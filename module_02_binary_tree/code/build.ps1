[CmdletBinding()]
param(
    [ValidateSet("starter", "solution", "autopsy")]
    [string]$Target = "starter",

    [switch]$Extensions,

    [switch]$StudentTests,

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

if ($Target -eq "autopsy") {
    if ($Extensions -or $StudentTests) {
        throw "Autopsy cannot be combined with a normal test switch."
    }

    $sources = @(
        (Join-Path $codeRoot "autopsy\faulty_links.c")
    )
    $outputName = "link_autopsy"
} else {
    if ($Extensions -and $StudentTests) {
        throw "Choose either -Extensions or -StudentTests, not both."
    }

    $implementation = Join-Path $codeRoot "$Target\tree_arena.c"

    if ($StudentTests) {
        $testSource = Join-Path $codeRoot "tests\test_student.c"
        $outputName = "${Target}_student_tests"
    } elseif ($Extensions) {
        $testSource = Join-Path $codeRoot "tests\test_extension.c"
        $outputName = "${Target}_extension"
    } else {
        $testSource = Join-Path $codeRoot "tests\test_core.c"
        $outputName = "${Target}_core"
    }

    $sources = @($implementation, $testSource)
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
