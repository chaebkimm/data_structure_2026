[CmdletBinding()]
param(
    [ValidateSet("lab", "starter", "solution", "autopsy")]
    [string]$Target = "lab",

    [switch]$Extensions,

    [switch]$StudentTests,

    [switch]$Comparison,

    [switch]$CompileOnly,

    [switch]$Sanitize,

    [switch]$UnsafeAutopsy
)

$ErrorActionPreference = "Stop"

$codeRoot = $PSScriptRoot
$includeDirectory = Join-Path $codeRoot "include"
$moduleRoot = Split-Path -Parent $codeRoot
$labDirectory = Join-Path $moduleRoot "student"
$treeRoot = Split-Path -Parent $moduleRoot
$buildDirectory = Join-Path $codeRoot $(if ($Sanitize) { "build-sanitize" } else { "build" })

New-Item -ItemType Directory -Force -Path $buildDirectory |
    Out-Null

$clangCommand = Get-Command "clang" -ErrorAction SilentlyContinue |
    Select-Object -First 1
$gccCommand = Get-Command "gcc" -ErrorAction SilentlyContinue |
    Select-Object -First 1
$msvcCommand = Get-Command "cl" -ErrorAction SilentlyContinue |
    Select-Object -First 1

if ($clangCommand) {
    $compiler = $clangCommand
    $compilerKind = "clang"
} elseif ($gccCommand) {
    $compiler = $gccCommand
    $compilerKind = "gcc"
} elseif ($msvcCommand) {
    $compiler = $msvcCommand
    $compilerKind = "msvc"
} else {
    throw @"
No supported C compiler was found on PATH.
Install or activate Clang, GCC/MinGW-w64, or use a Visual Studio Developer
PowerShell, then rerun this command.
"@
}

$testingBuild = $false
$runProgram = -not $CompileOnly
$extraDefinitions = @()

if ($Target -eq "lab") {
    if ($Extensions -or $UnsafeAutopsy) {
        throw "The current lab has no extension or unsafe-autopsy target."
    }
    if ($Comparison -and $StudentTests) {
        throw "Choose either -Comparison or -StudentTests, not both."
    }
    if ($Comparison) {
        $testName = "compare_lab"
    } elseif ($StudentTests) {
        $testName = "test_lab_student"
    } else {
        $testName = "test_lab_core"
    }
    $sources = @((Join-Path $codeRoot "tests/$testName.c"))
    $outputName = $testName
} elseif ($Target -eq "autopsy") {
    if ($Comparison) { throw "-Comparison requires -Target lab." }
    if ($Extensions -or $StudentTests) {
        throw "Autopsy cannot be combined with a normal test switch."
    }

    $sources = @(
        (Join-Path $codeRoot "autopsy\faulty_left_rotation.c")
    )

    if ($UnsafeAutopsy) {
        if (-not $Sanitize) {
            throw "-UnsafeAutopsy requires -Sanitize."
        }
        $outputName = "left_rotation_autopsy_unsafe"
        $runProgram = $false
    } else {
        $outputName = "left_rotation_autopsy_inspect"
        $extraDefinitions += "AUTOPSY_INSPECT_ONLY"
    }
} else {
    if ($Comparison) { throw "-Comparison requires -Target lab." }
    if ($UnsafeAutopsy) {
        throw "-UnsafeAutopsy requires -Target autopsy."
    }
    if ($Extensions -and $StudentTests) {
        throw "Choose either -Extensions or -StudentTests, not both."
    }

    $sources = @(
        (Join-Path $codeRoot "support\tree_support.c"),
        (Join-Path $codeRoot "$Target\avl_rotations.c"),
        (Join-Path $codeRoot "$Target\avl_tree.c")
    )
    $testingBuild = $true

    if ($StudentTests) {
        $sources += Join-Path $codeRoot "tests\test_student.c"
        $outputName = "${Target}_student_tests"
    } elseif ($Extensions) {
        $sources += Join-Path $codeRoot "tests\test_extension.c"
        $outputName = "${Target}_extension"
    } else {
        $sources += Join-Path $codeRoot "tests\test_core.c"
        $outputName = "${Target}_core"
    }
}

$outputExecutable = Join-Path $buildDirectory "$outputName.exe"

if ($compilerKind -eq "msvc") {
    $arguments = @(
        "/nologo",
        "/std:c11",
        "/W4",
        "/Zi",
        "/I$includeDirectory",
        "/I$labDirectory",
        "/I$treeRoot",
        "/Fo:$buildDirectory\"
    )

    if ($testingBuild) {
        $arguments += "/DTREE_TESTING"
    }
    foreach ($definition in $extraDefinitions) {
        $arguments += "/D$definition"
    }
    if ($Sanitize) {
        $arguments += @("/Od", "/fsanitize=address")
    }

    $arguments += $sources
    $arguments += "/Fe:$outputExecutable"
} else {
    $arguments = @(
        "-std=c11",
        "-Wall",
        "-Wextra",
        "-Wpedantic",
        "-Wconversion",
        "-Wshadow",
        "-g",
        "-I$includeDirectory",
        "-I$labDirectory",
        "-I$treeRoot"
    )

    if ($testingBuild) {
        $arguments += "-DTREE_TESTING"
    }
    foreach ($definition in $extraDefinitions) {
        $arguments += "-D$definition"
    }
    if ($Sanitize) {
        $arguments += @(
            "-fsanitize=address,undefined",
            "-fno-omit-frame-pointer"
        )
    }

    $arguments += $sources
    $arguments += @("-o", $outputExecutable)
}

Write-Host "Compiler: $($compiler.Source)"
Write-Host "Building: $outputName"
& $compiler.Source @arguments
if ($LASTEXITCODE -ne 0) {
    throw "Compilation failed with exit code $LASTEXITCODE."
}

if ($runProgram) {
    & $outputExecutable
    if ($LASTEXITCODE -ne 0) {
        throw "Program returned exit code $LASTEXITCODE."
    }
} elseif ($UnsafeAutopsy) {
    Write-Warning @"
The actual leak-autopsy binary was compiled but not run:
$outputExecutable
Run it only in an instructor-controlled disposable environment.
"@
} else {
    Write-Host "Compiled without running: $outputExecutable"
}
