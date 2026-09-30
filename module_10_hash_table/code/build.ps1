[CmdletBinding()]
param(
    [ValidateSet("starter", "solution", "autopsy")]
    [string]$Target = "solution",

    [switch]$Extensions,

    [switch]$StudentTests,

    [switch]$CompileOnly,

    [switch]$Sanitize
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

if ($Extensions -and $StudentTests) {
    throw "Choose either -Extensions or -StudentTests, not both."
}
if ($Target -eq "autopsy" -and ($Extensions -or $StudentTests)) {
    throw "Autopsy cannot be combined with a normal test switch."
}

$testingBuild = $Target -ne "autopsy"
if ($Target -eq "autopsy") {
    $sources = @(
        (Join-Path $codeRoot "autopsy\faulty_delete_empty.c")
    )
    $outputName = "hash_table_autopsy"
} else {
    $sources = @(
        (Join-Path $codeRoot "$Target\hash_table.c")
    )
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
        "/Fo:$buildDirectory\",
        "/Fd:$buildDirectory\$outputName.compiler.pdb"
    )
    if ($testingBuild) {
        $arguments += "/DHASH_TABLE_TESTING"
    }
    if ($Sanitize) {
        $arguments += @("/Od", "/fsanitize=address")
    }
    $arguments += $sources
    $arguments += @(
        "/Fe:$outputExecutable",
        "/link",
        "/PDB:$buildDirectory\$outputName.pdb",
        "/INCREMENTAL:NO"
    )
} else {
    $arguments = @(
        "-std=c11",
        "-Wall",
        "-Wextra",
        "-Wpedantic",
        "-Wconversion",
        "-Wshadow",
        "-g"
    )
    if ($testingBuild) {
        $arguments += "-DHASH_TABLE_TESTING"
        $arguments += "-I$includeDirectory"
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

if (-not $CompileOnly) {
    & $outputExecutable
    if ($LASTEXITCODE -ne 0) {
        throw "Program returned exit code $LASTEXITCODE."
    }
}
