[CmdletBinding()]
param(
    [ValidateSet("lab", "lab-compile", "core", "student-tests", "comparison")]
    [string]$Target = "lab",
    [switch]$StudentTests,
    [switch]$CompileOnly,
    [switch]$Sanitize
)
$ErrorActionPreference = "Stop"
$codeRoot = $PSScriptRoot
$moduleRoot = Split-Path -Parent $codeRoot
$labDirectory = Join-Path $moduleRoot "student"
$buildDirectory = Join-Path $codeRoot $(if ($Sanitize) { "build-sanitize" } else { "build" })
New-Item -ItemType Directory -Force -Path $buildDirectory | Out-Null
$compiler = Get-Command "clang", "gcc", "cl" -ErrorAction SilentlyContinue |
    Select-Object -First 1
if (-not $compiler) { throw "Activate a Clang, GCC, or Visual Studio C compiler." }
if ($StudentTests) {
    if ($Target -ne "lab") { throw "Use -Target student-tests or -StudentTests alone." }
    $Target = "student-tests"
}
$name = switch ($Target) {
    "comparison" { "compare_lab" }
    "student-tests" { "test_lab_student" }
    default { "test_lab" }
}
$objectOnly = $Target -eq "lab-compile"
$source = if ($objectOnly) { Join-Path $labDirectory "lab.c" } else { Join-Path $codeRoot "tests/$name.c" }
$output = Join-Path $buildDirectory $(if ($objectOnly) { "lab.obj" } else { "$name.exe" })
if ($compiler.Name -eq "cl.exe" -or $compiler.Name -eq "cl") {
    $arguments = @("/nologo", "/std:c11", "/W4", "/Zi", "/I$labDirectory")
    if ($Sanitize) { $arguments += @("/Od", "/fsanitize=address") }
    if ($objectOnly) { $arguments += @("/c", "/Fo:$output") }
    else { $arguments += @("/Fo:$buildDirectory\", "/Fe:$output") }
    $arguments += $source
} else {
    $arguments = @("-std=c11", "-Wall", "-Wextra", "-Wpedantic", "-Wconversion", "-Wshadow", "-g", "-I$labDirectory")
    if ($Sanitize) { $arguments += @("-fsanitize=address,undefined", "-fno-omit-frame-pointer") }
    if ($objectOnly) { $arguments += "-c" }
    $arguments += @($source, "-o", $output)
}
& $compiler.Source @arguments
if ($LASTEXITCODE -ne 0) { throw "Compilation failed: $LASTEXITCODE" }
if (-not $CompileOnly -and -not $objectOnly) {
    & $output
    if ($LASTEXITCODE -ne 0) { throw "Test failed: $LASTEXITCODE" }
}
