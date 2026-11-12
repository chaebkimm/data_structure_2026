[CmdletBinding()]
param([ValidateSet("all", "core", "student", "demo")][string]$Target = "all", [switch]$Sanitize)
$ErrorActionPreference = "Stop"
$buildDirectory = Join-Path $PSScriptRoot "build"
New-Item -ItemType Directory -Force -Path $buildDirectory | Out-Null
$compiler = Get-Command "clang", "gcc", "cl" -ErrorAction SilentlyContinue | Select-Object -First 1
if (-not $compiler) { throw "A C11 compiler is required." }
$labDirectory = Join-Path $PSScriptRoot "..\student"
$sources = @{ core = (Join-Path $PSScriptRoot "tests\test_lab_core.c"); student = (Join-Path $PSScriptRoot "tests\test_lab_student.c"); demo = (Join-Path $labDirectory "lab_driver.c") }
$targets = if ($Target -eq "all") { @("core", "student", "demo") } else { @($Target) }
foreach ($name in $targets) {
    $outputExecutable = Join-Path $buildDirectory "$name.exe"
    if ($compiler.Name -match "^cl(\.exe)?$") {
        $arguments = @("/nologo", "/std:c11", "/W4", "/I$labDirectory")
        if ($Sanitize) { $arguments += "/fsanitize=address" }
        $arguments += @($sources[$name], "/Fe:$outputExecutable")
    } else {
        $arguments = @("-std=c11", "-Wall", "-Wextra", "-Wpedantic", "-I$labDirectory")
        if ($Sanitize) { $arguments += @("-fsanitize=address,undefined", "-fno-omit-frame-pointer") }
        $arguments += @($sources[$name], "-o", $outputExecutable)
    }
    & $compiler.Source @arguments
    if ($LASTEXITCODE -ne 0) { throw "Compilation failed: $LASTEXITCODE" }
    & $outputExecutable
    if ($LASTEXITCODE -ne 0) { throw "Checks failed: $LASTEXITCODE" }
}
