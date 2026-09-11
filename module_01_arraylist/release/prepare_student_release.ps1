[CmdletBinding()]
param()

$ErrorActionPreference = "Stop"

Add-Type -AssemblyName System.IO.Compression
Add-Type -AssemblyName System.IO.Compression.FileSystem

$moduleRoot = Split-Path -Parent $PSScriptRoot
$distDirectory = Join-Path $moduleRoot "dist"

$stages = @(
    @{
        Name = "module_01_stage_a_initial_inquiry.zip"
        Entries = @(
            @{
                Source = "release\stage_a_README.md"
                Entry = "README.md"
            },
            @{
                Source = "student\inquiry_prompt.md"
                Entry = "inquiry_prompt.md"
            },
            @{
                Source = "student\inquiry_prompt_linear.md"
                Entry = "inquiry_prompt_linear.md"
            }
        )
    },
    @{
        Name = "module_01_stage_b_memory_model_pause.zip"
        Entries = @(
            @{
                Source = "release\stage_b_README.md"
                Entry = "README.md"
            },
            @{
                Source = "student\representation_reveal.md"
                Entry = "representation_reveal.md"
            },
            @{
                Source = "student\vocabulary.md"
                Entry = "vocabulary.md"
            },
            @{
                Source = "student\cognitive_pause.md"
                Entry = "cognitive_pause.md"
            }
        )
    },
    @{
        Name = "module_01_stage_c_investigation.zip"
        Entries = @(
            @{
                Source = "release\stage_c_README.md"
                Entry = "README.md"
            },
            @{
                Source = "student\investigation_worksheet.md"
                Entry = "investigation_worksheet.md"
            },
            @{
                Source = "student\investigation_worksheet_linear.md"
                Entry = "investigation_worksheet_linear.md"
            }
        )
    },
    @{
        Name = "module_01_stage_d_calibrated_notes.zip"
        Entries = @(
            @{
                Source = "release\stage_d_README.md"
                Entry = "README.md"
            },
            @{
                Source = "student\notes.md"
                Entry = "notes.md"
            },
            @{
                Source = "student\textbook.md"
                Entry = "textbook.md"
            },
            @{
                Source = "student\textbook_korean.md"
                Entry = "textbook_korean.md"
            },
            @{
                Source = "diagrams\memory_models.md"
                Entry = "diagrams/memory_models.md"
            }
        )
    },
    @{
        Name = "module_01_stage_e_lab.zip"
        Entries = @(
            @{
                Source = "release\stage_e_README.md"
                Entry = "README.md"
            },
            @{
                Source = "student\lab.md"
                Entry = "student/lab.md"
            },
            @{
                Source = "student\day2_plan.md"
                Entry = "student/day2_plan.md"
            },
            @{
                Source = "student\evidence_template.md"
                Entry = "student/evidence_template.md"
            },
            @{
                Source = "student\rubric.md"
                Entry = "student/rubric.md"
            },
            @{
                Source = "student\segfault_autopsy.md"
                Entry = "student/segfault_autopsy.md"
            },
            @{
                Source = "release\student_code_README.md"
                Entry = "code/README.md"
            },
            @{
                Source = "release\student_build.ps1"
                Entry = "code/build.ps1"
            },
            @{
                Source = "release\student_Makefile"
                Entry = "code/Makefile"
            },
            @{
                Source = "code\include\int_list.h"
                Entry = "code/include/int_list.h"
            },
            @{
                Source = "code\starter\int_list.c"
                Entry = "code/starter/int_list.c"
            },
            @{
                Source = "code\tests\test_core.c"
                Entry = "code/tests/test_core.c"
            },
            @{
                Source = "code\tests\test_extension.c"
                Entry = "code/tests/test_extension.c"
            },
            @{
                Source = "code\tests\test_student.c"
                Entry = "code/tests/test_student.c"
            },
            @{
                Source = "code\autopsy\README.md"
                Entry = "code/autopsy/README.md"
            },
            @{
                Source = "code\autopsy\faulty_append.c"
                Entry = "code/autopsy/faulty_append.c"
            }
        )
    }
)

New-Item -ItemType Directory -Force -Path $distDirectory | Out-Null

foreach ($stage in $stages) {
    $archivePath = Join-Path $distDirectory $stage.Name
    if (Test-Path -LiteralPath $archivePath) {
        throw "Refusing to overwrite existing archive: $archivePath"
    }

    foreach ($item in $stage.Entries) {
        $sourcePath = Join-Path $moduleRoot $item.Source
        if (-not (Test-Path -LiteralPath $sourcePath -PathType Leaf)) {
            throw "Required release source is missing: $sourcePath"
        }
    }
}

foreach ($stage in $stages) {
    $archivePath = Join-Path $distDirectory $stage.Name
    $fileStream = [System.IO.File]::Open(
        $archivePath,
        [System.IO.FileMode]::CreateNew,
        [System.IO.FileAccess]::ReadWrite,
        [System.IO.FileShare]::None
    )
    $archive = New-Object System.IO.Compression.ZipArchive(
        $fileStream,
        [System.IO.Compression.ZipArchiveMode]::Create,
        $false
    )

    try {
        foreach ($item in $stage.Entries) {
            $sourcePath = Join-Path $moduleRoot $item.Source
            $zipEntry = $archive.CreateEntry(
                $item.Entry,
                [System.IO.Compression.CompressionLevel]::Optimal
            )
            $inputStream = [System.IO.File]::OpenRead($sourcePath)
            $outputStream = $zipEntry.Open()

            try {
                $inputStream.CopyTo($outputStream)
            } finally {
                $outputStream.Dispose()
                $inputStream.Dispose()
            }
        }
    } finally {
        $archive.Dispose()
        $fileStream.Dispose()
    }

    Write-Host "Created $archivePath"
}

Get-ChildItem -LiteralPath $distDirectory -Filter "module_01_stage_*.zip" |
    Get-FileHash -Algorithm SHA256 |
    Select-Object Path, Hash
