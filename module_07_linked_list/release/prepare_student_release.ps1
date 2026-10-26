[CmdletBinding()]
param([string]$OutputPath = "")

$ErrorActionPreference = "Stop"
$packager = Join-Path $PSScriptRoot "prepare_student_release.py"
$python = Get-Command "python3", "python" -ErrorAction SilentlyContinue |
    Select-Object -First 1
if (-not $python) {
    throw "Python 3 is required. Run release/prepare_student_release.py with your Python 3 interpreter."
}

$arguments = @($packager)
if ($OutputPath) {
    $arguments += @("--output", $OutputPath)
}
& $python.Source @arguments
if ($LASTEXITCODE -ne 0) {
    throw "Week 7 packaging failed with exit code $LASTEXITCODE."
}
