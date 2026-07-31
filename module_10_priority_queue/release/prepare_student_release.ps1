[CmdletBinding()]
param()

$ErrorActionPreference = "Stop"

Add-Type -AssemblyName System.IO.Compression
Add-Type -AssemblyName System.IO.Compression.FileSystem

$moduleRoot = Split-Path -Parent $PSScriptRoot
$distDirectory = Join-Path $moduleRoot "dist"

$stages = @(
    @{
        Name = "module_10_stage_a_initial_inquiry.zip"
        Entries = @(
            @{ Source = "release\stage_a_README.md"; Entry = "README.md" },
            @{ Source = "student\inquiry_prompt.md"; Entry = "inquiry_prompt.md" },
            @{ Source = "student\inquiry_prompt_linear.md"; Entry = "inquiry_prompt_linear.md" }
        )
    },
    @{
        Name = "module_10_stage_b_representation_pause.zip"
        Entries = @(
            @{ Source = "release\stage_b_README.md"; Entry = "README.md" },
            @{ Source = "student\representation_reveal.md"; Entry = "representation_reveal.md" },
            @{ Source = "student\cognitive_pause.md"; Entry = "cognitive_pause.md" },
            @{ Source = "student\vocabulary.md"; Entry = "vocabulary.md" }
        )
    },
    @{
        Name = "module_10_stage_c_investigation.zip"
        Entries = @(
            @{ Source = "release\stage_c_README.md"; Entry = "README.md" },
            @{ Source = "student\investigation_worksheet.md"; Entry = "investigation_worksheet.md" },
            @{ Source = "student\investigation_worksheet_linear.md"; Entry = "investigation_worksheet_linear.md" }
        )
    },
    @{
        Name = "module_10_stage_d_textbook_models.zip"
        Entries = @(
            @{ Source = "release\stage_d_README.md"; Entry = "README.md" },
            @{ Source = "student\textbook.md"; Entry = "textbook.md" },
            @{ Source = "diagrams\priority_queue_models.md"; Entry = "diagrams/priority_queue_models.md" }
        )
    },
    @{
        Name = "module_10_stage_e_lab.zip"
        Entries = @(
            @{ Source = "release\stage_e_README.md"; Entry = "README.md" },
            @{ Source = "student\lab.md"; Entry = "student/lab.md" },
            @{ Source = "student\evidence_template.md"; Entry = "student/evidence_template.md" },
            @{ Source = "student\rubric.md"; Entry = "student/rubric.md" },
            @{ Source = "student\priority_queue_autopsy.md"; Entry = "student/priority_queue_autopsy.md" },
            @{ Source = "release\student_code_README.md"; Entry = "code/README.md" },
            @{ Source = "release\student_build.ps1"; Entry = "code/build.ps1" },
            @{ Source = "release\student_Makefile"; Entry = "code/Makefile" },
            @{ Source = "code\include\alert_priority_queue.h"; Entry = "code/include/alert_priority_queue.h" },
            @{ Source = "code\starter\alert_priority_queue.c"; Entry = "code/starter/alert_priority_queue.c" },
            @{ Source = "code\tests\test_core.c"; Entry = "code/tests/test_core.c" },
            @{ Source = "code\tests\test_student.c"; Entry = "code/tests/test_student.c" },
            @{ Source = "code\autopsy\README.md"; Entry = "code/autopsy/README.md" },
            @{ Source = "code\autopsy\faulty_tie.c"; Entry = "code/autopsy/faulty_tie.c" }
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

$createdArchives = @()

try {
    foreach ($stage in $stages) {
        $archivePath = Join-Path $distDirectory $stage.Name
        $temporaryName = ".{0}.{1}.partial" -f @(
            $stage.Name,
            [Guid]::NewGuid().ToString("N")
        )
        $temporaryPath = Join-Path $distDirectory $temporaryName
        $fileStream = $null
        $archive = $null

        try {
            $fileStream = [System.IO.File]::Open(
                $temporaryPath,
                [System.IO.FileMode]::CreateNew,
                [System.IO.FileAccess]::ReadWrite,
                [System.IO.FileShare]::None
            )
            $archive = New-Object System.IO.Compression.ZipArchive(
                $fileStream,
                [System.IO.Compression.ZipArchiveMode]::Create,
                $false
            )

            foreach ($item in $stage.Entries) {
                $sourcePath = Join-Path $moduleRoot $item.Source
                $zipEntry = $archive.CreateEntry(
                    $item.Entry,
                    [System.IO.Compression.CompressionLevel]::Optimal
                )
                $inputStream = $null
                $outputStream = $null

                try {
                    $inputStream = [System.IO.File]::OpenRead($sourcePath)
                    $outputStream = $zipEntry.Open()
                    $inputStream.CopyTo($outputStream)
                } finally {
                    if ($null -ne $outputStream) {
                        $outputStream.Dispose()
                    }
                    if ($null -ne $inputStream) {
                        $inputStream.Dispose()
                    }
                }
            }

            $archive.Dispose()
            $archive = $null
            $fileStream.Dispose()
            $fileStream = $null

            [System.IO.File]::Move($temporaryPath, $archivePath)
            $createdArchives += $archivePath
        } finally {
            if ($null -ne $archive) {
                $archive.Dispose()
            }
            if ($null -ne $fileStream) {
                $fileStream.Dispose()
            }
            if (Test-Path -LiteralPath $temporaryPath) {
                Remove-Item -LiteralPath $temporaryPath -Force
            }
        }

        Write-Host "Created $archivePath"
    }
} catch {
    foreach ($createdArchive in $createdArchives) {
        if (Test-Path -LiteralPath $createdArchive) {
            Remove-Item -LiteralPath $createdArchive -Force
        }
    }
    throw
}

$createdHashes = foreach ($archivePath in $createdArchives) {
    Get-FileHash -LiteralPath $archivePath -Algorithm SHA256
}

$createdHashes | Select-Object Path, Hash
