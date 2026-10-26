[CmdletBinding()]
param(
    [switch]$StudentTests,
    [switch]$Comparison,
    [switch]$CompileOnly,
    [switch]$Sanitize
)

$ErrorActionPreference = "Stop"
if ($StudentTests -and $Comparison) {
    throw "Select either -StudentTests or -Comparison."
}
$codeRoot = $PSScriptRoot
$treeRoot = Split-Path -Parent $codeRoot
$labDirectory = Join-Path $treeRoot "student"
$buildDirectory = Join-Path $codeRoot $(if ($Sanitize) { "build-sanitize" } else { "build" })
New-Item -ItemType Directory -Force -Path $buildDirectory | Out-Null
$compiler = Get-Command "clang", "gcc", "cl" -ErrorAction SilentlyContinue |
    Select-Object -First 1
if (-not $compiler) { throw "Activate a Clang, GCC, or Visual Studio C compiler." }
if ($Comparison) { $name = "compare_lab" }
elseif ($StudentTests) { $name = "test_lab_student" }
else { $name = "test_lab_core" }
$source = Join-Path $codeRoot "tests/$name.c"
$output = Join-Path $buildDirectory "$name.exe"
if ($compiler.Name -eq "cl.exe" -or $compiler.Name -eq "cl") {
    $arguments = @("/nologo", "/std:c11", "/W4", "/I$labDirectory", "/I$treeRoot",
        "/Fo:$buildDirectory\", "/Fe:$output")
    if ($Sanitize) { $arguments += "/fsanitize=address" }
    $arguments += $source
} else {
    $arguments = @("-std=c11", "-Wall", "-Wextra", "-Wpedantic", "-Wconversion",
        "-Wshadow", "-g", "-I$labDirectory", "-I$treeRoot")
    if ($Sanitize) {
        $arguments += @("-fsanitize=address,undefined", "-fno-omit-frame-pointer")
    }
    $arguments += @($source, "-o", $output)
}
& $compiler.Source @arguments
if ($LASTEXITCODE -ne 0) { throw "Compilation failed: $LASTEXITCODE" }
if (-not $CompileOnly) {
    & $output
    if ($LASTEXITCODE -ne 0) { throw "Driver failed: $LASTEXITCODE" }
}
