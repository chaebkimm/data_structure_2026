[CmdletBinding()]
param(
    [ValidateSet("starter", "solution", "autopsy")]
    [string]$Target = "starter",

    [switch]$Extensions,

    [switch]$StudentTests,

    [switch]$AllocationFailure,

    [switch]$Sanitize,

    [switch]$InspectOnly
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
Install/activate Clang, GCC/MinGW-w64, or use a Visual Studio Developer
PowerShell, then rerun this command.
"@
}

if ($Target -eq "autopsy") {
    if ($Extensions -or $StudentTests -or $AllocationFailure) {
        throw "Autopsy cannot be combined with a normal test switch."
    }

    $sources = @(
        (Join-Path $codeRoot "autopsy\faulty_append.c")
    )
    $outputName = "autopsy"
} else {
    $implementation = Join-Path $codeRoot "$Target\int_list.c"

    $selectedTestCount = @(
        $Extensions,
        $StudentTests,
        $AllocationFailure
    ).Where({ $_ }).Count
    if ($selectedTestCount -gt 1) {
        throw @"
Choose at most one of -Extensions, -StudentTests, or -AllocationFailure.
"@
    }

    if ($AllocationFailure) {
        $testSource = Join-Path $codeRoot "tests\test_allocation_failure.c"
        $outputName = "${Target}_allocation_failure"
    } elseif ($StudentTests) {
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

    if ($AllocationFailure) {
        $arguments += "/DINT_LIST_TESTING"
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

    if ($AllocationFailure) {
        $arguments += "-DINT_LIST_TESTING"
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

if ($Target -eq "autopsy") {
    if ($InspectOnly) {
        & $outputExecutable "--inspect-only"
        if ($LASTEXITCODE -ne 0) {
            throw "Autopsy inspection returned exit code $LASTEXITCODE."
        }

        Write-Host "Inspection completed without triggering the fault."
    } else {
        & $outputExecutable
        if ($LASTEXITCODE -eq 0) {
            Write-Warning @"
The intentional undefined behavior returned zero on this run. Rebuild with
-Sanitize or use a debugger; a crash is not guaranteed by the C language.
"@
        } else {
            Write-Host (
                "Fault observed as intended; process exit code: " +
                $LASTEXITCODE
            )
        }
    }

    return
}

& $outputExecutable
if ($LASTEXITCODE -ne 0) {
    throw "Test executable returned exit code $LASTEXITCODE."
}
