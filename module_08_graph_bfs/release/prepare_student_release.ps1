[CmdletBinding()]
param([string]$OutputPath = "")
$ErrorActionPreference = "Stop"
$packager = Join-Path $PSScriptRoot "prepare_student_release.py"
$python = Get-Command "python3", "python" -ErrorAction SilentlyContinue | Select-Object -First 1
if (-not $python) { throw "Python3 is required to run prepare_student_release.py." }
$arguments = @($packager)
if ($OutputPath) { $arguments += @("--output", $OutputPath) }
& $python.Source @arguments
if ($LASTEXITCODE -ne 0) { throw "Module8 packaging failed: $LASTEXITCODE" }
