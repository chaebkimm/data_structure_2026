[CmdletBinding()]
param(
    [ValidateSet("starter", "solution", "lecture", "lab-tests", "autopsy")]
    [string]$Target = "lecture",

    [switch]$Extensions,

    [switch]$StudentTests,

    [switch]$Sanitize
)

$ErrorActionPreference = "Stop"

$codeRoot = $PSScriptRoot
$includeDirectory = Join-Path $codeRoot "include"
$repositoryRoot = Split-Path -Parent (Split-Path -Parent $codeRoot)
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

if ($Target -eq "lecture" -or $Target -eq "lab-tests") {
    if ($Extensions -or $StudentTests) {
        throw "Lecture and lab-tests cannot be combined with the optional API test switches."
    }

    if ($Target -eq "lab-tests") {
        $sources = @((Join-Path $codeRoot "tests\test_lab.c"))
        $outputName = "lab_tests"
    } else {
        $sources = @((Join-Path $codeRoot "lecture\lab_demo.c"))
        $outputName = "lab_demo"
    }
} elseif ($Target -eq "autopsy") {
    if ($Extensions -or $StudentTests) {
        throw "Autopsy cannot be combined with a normal test switch."
    }

    $sources = @(
        (Join-Path $codeRoot "support\tree_support.c"),
        (Join-Path $codeRoot "autopsy\faulty_preorder.c")
    )
    $outputName = "tree_dfs_autopsy"
} else {
    if ($Extensions -and $StudentTests) {
        throw "Choose either -Extensions or -StudentTests, not both."
    }

    $sources = @(
        (Join-Path $codeRoot "support\tree_support.c"),
        (Join-Path $codeRoot "$Target\tree_dfs.c")
    )

    if ($StudentTests) {
        $sources += Join-Path $codeRoot "tests\test_student.c"
        $outputName = "${Target}_student_tests"
    } elseif ($Extensions) {
        $sources += Join-Path $codeRoot "tests\test_extension.c"
        $outputName = "${Target}_extension"
        $testingBuild = $true
    } else {
        $sources += Join-Path $codeRoot "tests\test_core.c"
        $outputName = "${Target}_core"
        $testingBuild = $true
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
        "/I$repositoryRoot"
    )

    if ($testingBuild) {
        $arguments += "/DTREE_DFS_TESTING"
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
        "-I$repositoryRoot"
    )

    if ($testingBuild) {
        $arguments += "-DTREE_DFS_TESTING"
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

& $outputExecutable
if ($LASTEXITCODE -ne 0) {
    throw "Program returned exit code $LASTEXITCODE."
}
