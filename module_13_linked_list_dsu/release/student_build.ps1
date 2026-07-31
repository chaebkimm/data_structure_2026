[CmdletBinding()]
param(
    [ValidateSet("starter", "autopsy")]
    [string]$Target = "starter",

    [switch]$StudentTests,

    [switch]$Sanitize,

    [switch]$UnsafeAutopsy
)

$ErrorActionPreference = "Stop"

$codeRoot = $PSScriptRoot
$includeDirectory = Join-Path $codeRoot "include"
$buildDirectory = Join-Path $codeRoot "build"

New-Item -ItemType Directory -Force -Path $buildDirectory | Out-Null

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
$runProgram = $true
$extraDefinitions = @()

if ($Target -eq "autopsy") {
    if ($StudentTests) {
        throw "Autopsy cannot be combined with -StudentTests."
    }

    $sources = @(
        (Join-Path $codeRoot "autopsy\faulty_linked_delete.c")
    )
    if ($UnsafeAutopsy) {
        if (-not $Sanitize) {
            throw "-UnsafeAutopsy requires -Sanitize."
        }
        $outputName = "linked_delete_autopsy_unsafe"
        $runProgram = $false
    } else {
        $outputName = "linked_delete_autopsy_inspect"
        $extraDefinitions += "AUTOPSY_INSPECT_ONLY"
    }
} else {
    if ($UnsafeAutopsy) {
        throw "-UnsafeAutopsy requires -Target autopsy."
    }

    $sources = @(
        (Join-Path $codeRoot "starter\linked_list.c"),
        (Join-Path $codeRoot "starter\dsu.c"),
        (Join-Path $codeRoot "support\undirected_edge_list.c")
    )
    $testingBuild = $true

    if ($StudentTests) {
        $sources += Join-Path $codeRoot "tests\test_student.c"
        $outputName = "starter_student_tests"
    } else {
        $sources += Join-Path $codeRoot "tests\test_core.c"
        $outputName = "starter_core"
    }
}

$outputExecutable = Join-Path $buildDirectory "$outputName.exe"

if ($compilerKind -eq "msvc") {
    $arguments = @(
        "/nologo",
        "/std:c11",
        "/W4",
        "/Zi",
        "/I$includeDirectory"
    )
    if ($testingBuild) {
        $arguments += "/DLINKED_LIST_TESTING"
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
        "-I$includeDirectory"
    )
    if ($testingBuild) {
        $arguments += "-DLINKED_LIST_TESTING"
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
} else {
    Write-Warning @"
The actual use-after-free binary was compiled with sanitizers but not run:
$outputExecutable
Do not run it outside an instructor-controlled disposable environment.
"@
}
