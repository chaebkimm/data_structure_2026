[CmdletBinding()]
param([ValidateSet("lab", "lecture")][string]$Target = "lab", [switch]$StudentTests, [switch]$Sanitize)
$ErrorActionPreference = "Stop"
$codeRoot = $PSScriptRoot
$buildDirectory = Join-Path $codeRoot "build"
New-Item -ItemType Directory -Force -Path $buildDirectory | Out-Null
$compiler = Get-Command "clang", "gcc", "cl" -ErrorAction SilentlyContinue | Select-Object -First 1
if (-not $compiler) { throw "A C11 compiler (Clang, GCC, or MSVC) is required." }
$outputExecutable = Join-Path $buildDirectory "lab_core.exe"
$source = Join-Path $codeRoot "tests\test_lecture.c"
if ($compiler.Name -match "^cl(\.exe)?$") {
    $arguments = @("/nologo", "/std:c11", "/W4")
    if ($Sanitize) { $arguments += "/fsanitize=address" }
    $arguments += @($source, "/Fe:$outputExecutable")
} else {
    $arguments = @("-std=c11", "-Wall", "-Wextra", "-pedantic")
    if ($Sanitize) { $arguments += @("-fsanitize=address,undefined", "-fno-omit-frame-pointer") }
    $arguments += @($source, "-o", $outputExecutable)
}
& $compiler.Source @arguments
if ($LASTEXITCODE -ne 0) { throw "Compilation failed: $LASTEXITCODE" }
& $outputExecutable
if ($LASTEXITCODE -ne 0) { throw "Tests failed: $LASTEXITCODE" }
