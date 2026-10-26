[CmdletBinding()]
param([switch]$StudentTests, [switch]$Sanitize)

$ErrorActionPreference = "Stop"
$moduleRoot = Split-Path -Parent $PSScriptRoot
$codeRoot = Join-Path $moduleRoot "code"
$labDirectory = Join-Path $moduleRoot "student"
$buildDirectory = Join-Path $codeRoot "build"
New-Item -ItemType Directory -Force -Path $buildDirectory | Out-Null

$compiler = Get-Command "clang", "gcc", "cl" -ErrorAction SilentlyContinue |
    Select-Object -First 1
if (-not $compiler) { throw "Activate a C11 compiler: Clang, GCC, or Visual Studio Developer PowerShell."
}
$testName = if ($StudentTests) { "student" } else { "core" }
$source = Join-Path $codeRoot "tests/test_lab_$testName.c"
$outputFile = Join-Path $buildDirectory "$testName.exe"
if ($compiler.Name -match '^cl(\.exe)?$') {
    $arguments = @("/nologo", "/std:c11", "/W4", "/Zi", "/I$labDirectory")
    if ($Sanitize) { $arguments += @("/Od", "/fsanitize=address") }
    $arguments += @($source, "/Fe:$outputFile")
} else {
    $arguments = @("-std=c11", "-Wall", "-Wextra", "-Wpedantic", "-Wconversion", "-Wshadow", "-g", "-I$labDirectory")
    if ($Sanitize) { $arguments += @("-fsanitize=address,undefined", "-fno-omit-frame-pointer") }
    $arguments += @($source, "-o", $outputFile)
}
& $compiler.Source @arguments
if ($LASTEXITCODE -ne 0) { throw "Compilation failed with exit code $LASTEXITCODE." }
& $outputFile
if ($LASTEXITCODE -ne 0) { throw "Test failed with exit code $LASTEXITCODE." }
