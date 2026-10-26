[CmdletBinding()]
param([string]$OutputDirectory = "")

$ErrorActionPreference = "Stop"
$python = Get-Command "python3", "python" -ErrorAction SilentlyContinue |
    Select-Object -First 1
if (-not $python) {
    throw "Python 3 is required to package the Module 09 lab and its Module 07 dependency."
}
$arguments = @((Join-Path $PSScriptRoot "prepare_student_release.py"))
if ($OutputDirectory) {
    $arguments += @("--output-dir", $OutputDirectory)
}
& $python.Source @arguments
if ($LASTEXITCODE -ne 0) {
    throw "Module 09 packaging failed with exit code $LASTEXITCODE."
}
