[CmdletBinding()]
param()

$ErrorActionPreference = "Stop"

Add-Type -AssemblyName System.IO.Compression
Add-Type -AssemblyName System.IO.Compression.FileSystem

$moduleRoot = Split-Path -Parent $PSScriptRoot
$distDirectory = Join-Path $moduleRoot "dist"
$codeBuildDirectory = Join-Path $moduleRoot "code\build"
$fixedEntryTimestamp = [DateTimeOffset]::Parse(
    "2000-01-01T00:00:00+00:00"
)

$stages = @(
    @{
        Name = "module_13_stage_a_initial_inquiry.zip"
        Entries = @(
            @{ Source = "release\stage_a_README.md"; Entry = "README.md" },
            @{ Source = "student\inquiry_prompt.md"; Entry = "inquiry_prompt.md" },
            @{ Source = "student\inquiry_prompt_linear.md"; Entry = "inquiry_prompt_linear.md" }
        )
    },
    @{
        Name = "module_13_stage_b_representation_pause.zip"
        Entries = @(
            @{ Source = "release\stage_b_README.md"; Entry = "README.md" },
            @{ Source = "student\representation_reveal.md"; Entry = "representation_reveal.md" },
            @{ Source = "student\cognitive_pause.md"; Entry = "cognitive_pause.md" },
            @{ Source = "student\vocabulary.md"; Entry = "vocabulary.md" }
        )
    },
    @{
        Name = "module_13_stage_c_investigation.zip"
        Entries = @(
            @{ Source = "release\stage_c_README.md"; Entry = "README.md" },
            @{ Source = "student\investigation_worksheet.md"; Entry = "investigation_worksheet.md" },
            @{ Source = "student\investigation_worksheet_linear.md"; Entry = "investigation_worksheet_linear.md" }
        )
    },
    @{
        Name = "module_13_stage_d_textbook_models.zip"
        Entries = @(
            @{ Source = "release\stage_d_README.md"; Entry = "README.md" },
            @{ Source = "student\textbook.md"; Entry = "textbook.md" },
            @{ Source = "diagrams\hash_table_models.md"; Entry = "diagrams/hash_table_models.md" }
        )
    },
    @{
        Name = "module_13_stage_e_lab.zip"
        Entries = @(
            @{ Source = "release\stage_e_README.md"; Entry = "README.md" },
            @{ Source = "student\lab.md"; Entry = "student/lab.md" },
            @{ Source = "student\evidence_template.md"; Entry = "student/evidence_template.md" },
            @{ Source = "student\rubric.md"; Entry = "student/rubric.md" },
            @{ Source = "student\hash_table_autopsy.md"; Entry = "student/hash_table_autopsy.md" },
            @{ Source = "release\student_code_README.md"; Entry = "code/README.md" },
            @{ Source = "release\student_build.ps1"; Entry = "code/build.ps1" },
            @{ Source = "release\student_Makefile"; Entry = "code/Makefile" },
            @{ Source = "code\include\hash_table.h"; Entry = "code/include/hash_table.h" },
            @{ Source = "code\starter\hash_table.c"; Entry = "code/starter/hash_table.c" },
            @{ Source = "code\tests\test_core.c"; Entry = "code/tests/test_core.c" },
            @{ Source = "code\tests\test_student.c"; Entry = "code/tests/test_student.c" },
            @{ Source = "code\autopsy\README.md"; Entry = "code/autopsy/README.md" },
            @{ Source = "code\autopsy\faulty_delete_empty.c"; Entry = "code/autopsy/faulty_delete_empty.c" }
        )
    }
)

$expectedStageCounts = @(3, 4, 3, 3, 14)
if ($stages.Count -ne $expectedStageCounts.Count) {
    throw "Internal release-map stage-count mismatch."
}

$archiveNames = @{}
for ($index = 0; $index -lt $stages.Count; $index += 1) {
    $stage = $stages[$index]
    if ($stage.Entries.Count -ne $expectedStageCounts[$index]) {
        throw "Internal release-map count mismatch for $($stage.Name)."
    }
    if ($archiveNames.ContainsKey($stage.Name)) {
        throw "Duplicate archive name in release map: $($stage.Name)"
    }
    $archiveNames[$stage.Name] = $true
}

$expectedSourceRelativePaths = @(
    "README.md",
    "diagrams\hash_table_models.md",
    "instructor\answer_key.md",
    "instructor\lesson_plan.md",
    "instructor\technical_notes.md",
    "student\cognitive_pause.md",
    "student\evidence_template.md",
    "student\hash_table_autopsy.md",
    "student\inquiry_prompt.md",
    "student\inquiry_prompt_linear.md",
    "student\investigation_worksheet.md",
    "student\investigation_worksheet_linear.md",
    "student\lab.md",
    "student\representation_reveal.md",
    "student\rubric.md",
    "student\textbook.md",
    "student\vocabulary.md",
    "release\prepare_student_release.ps1",
    "release\release_manifest.md",
    "release\stage_a_README.md",
    "release\stage_b_README.md",
    "release\stage_c_README.md",
    "release\stage_d_README.md",
    "release\stage_e_README.md",
    "release\student_build.ps1",
    "release\student_code_README.md",
    "release\student_Makefile",
    "code\README.md",
    "code\build.ps1",
    "code\Makefile",
    "code\include\hash_table.h",
    "code\starter\hash_table.c",
    "code\solution\hash_table.c",
    "code\tests\test_core.c",
    "code\tests\test_extension.c",
    "code\tests\test_student.c",
    "code\autopsy\README.md",
    "code\autopsy\faulty_delete_empty.c"
)

$uniqueExpectedSources = @(
    $expectedSourceRelativePaths | Sort-Object -Unique
)
if ($uniqueExpectedSources.Count -ne $expectedSourceRelativePaths.Count) {
    throw "Duplicate path in the expected source inventory."
}

$sourceFiles = @(
    Get-ChildItem -LiteralPath $moduleRoot -Recurse -File |
        Where-Object {
            $_.FullName -notlike "$distDirectory\*" -and
            $_.FullName -notlike "$codeBuildDirectory\*"
        }
)

$actualSourceRelativePaths = @(
    $sourceFiles |
        ForEach-Object {
            $_.FullName.Substring($moduleRoot.Length).TrimStart(
                [System.IO.Path]::DirectorySeparatorChar,
                [System.IO.Path]::AltDirectorySeparatorChar
            )
        }
)

$inventoryDifference = @(
    Compare-Object -ReferenceObject $expectedSourceRelativePaths `
        -DifferenceObject $actualSourceRelativePaths
)
if ($inventoryDifference.Count -ne 0) {
    $details = $inventoryDifference |
        ForEach-Object {
            "$($_.SideIndicator) $($_.InputObject)"
        }
    throw @"
Source inventory does not match the required 38-file package:
$($details -join [Environment]::NewLine)
"@
}

$markdownCount = @(
    $sourceFiles | Where-Object Extension -eq ".md"
).Count
$powershellCount = @(
    $sourceFiles | Where-Object Extension -eq ".ps1"
).Count
$cCount = @(
    $sourceFiles | Where-Object Extension -eq ".c"
).Count
$headerCount = @(
    $sourceFiles | Where-Object Extension -eq ".h"
).Count
$makefiles = @(
    $sourceFiles |
        Where-Object {
            $_.Name -eq "Makefile" -or
                $_.Name -eq "student_Makefile"
        }
)

if (
    $sourceFiles.Count -ne 38 -or
    $markdownCount -ne 26 -or
    $powershellCount -ne 3 -or
    $makefiles.Count -ne 2 -or
    $cCount -ne 6 -or
    $headerCount -ne 1
) {
    throw @"
Source inventory must be exactly 38 files before dist:
26 Markdown, 3 PowerShell, 2 Makefiles, 6 C, and 1 header.
Observed: total=$($sourceFiles.Count), md=$markdownCount, ps1=$powershellCount,
Makefiles=$($makefiles.Count), c=$cCount, h=$headerCount.
"@
}

$stageASources = @(
    "release\stage_a_README.md",
    "student\inquiry_prompt.md",
    "student\inquiry_prompt_linear.md"
)
$forbiddenStageATerms = @(
    "array",
    "map",
    "key",
    "slot",
    "capacity",
    "hash",
    "hash table",
    "hash function",
    "collision",
    "open addressing",
    "linear probing",
    "probe",
    "load factor",
    "tombstone",
    "rehash",
    "compaction",
    "HASH_SLOT_EMPTY",
    "HASH_SLOT_OCCUPIED",
    "HASH_SLOT_DELETED",
    "invariant",
    "validator",
    "expected O(1)",
    "complexity",
    "Big-O",
    "algorithm",
    "allocation",
    "calloc",
    "malloc",
    "free",
    "pointer",
    "struct",
    "API",
    "TODO",
    "pseudocode",
    "status",
    "solution",
    "answer key",
    "instructor",
    "denial of service",
    "DoS",
    "attacker",
    "cryptographic"
)

foreach ($relativePath in $stageASources) {
    $stageAPath = Join-Path $moduleRoot $relativePath
    $stageAText = Get-Content -LiteralPath $stageAPath -Raw

    foreach ($term in $forbiddenStageATerms) {
        $termPattern = "(?i)(?<![A-Za-z0-9_])" +
            [Regex]::Escape($term) +
            "(?![A-Za-z0-9_])"
        if ($stageAText -match $termPattern) {
            throw "Stage A embargo term '$term' found in $relativePath."
        }
    }

    if ($stageAText -match '```') {
        throw "Stage A fenced code or text block found in $relativePath."
    }
    if ($stageAText -match "(?i)(?<![A-Za-z0-9_])O\s*\(") {
        throw "Stage A complexity notation found in $relativePath."
    }
}

$modulePrefix = $moduleRoot.TrimEnd(
    [System.IO.Path]::DirectorySeparatorChar,
    [System.IO.Path]::AltDirectorySeparatorChar
) + [System.IO.Path]::DirectorySeparatorChar
$distPrefix = $distDirectory.TrimEnd(
    [System.IO.Path]::DirectorySeparatorChar,
    [System.IO.Path]::AltDirectorySeparatorChar
) + [System.IO.Path]::DirectorySeparatorChar

foreach ($stage in $stages) {
    $archivePath = [System.IO.Path]::GetFullPath(
        (Join-Path $distDirectory $stage.Name)
    )
    if (-not $archivePath.StartsWith(
        $distPrefix,
        [System.StringComparison]::OrdinalIgnoreCase
    )) {
        throw "Archive path escapes dist: $archivePath"
    }
    if (Test-Path -LiteralPath $archivePath) {
        throw "Refusing to overwrite existing archive: $archivePath"
    }

    $entryNames = @{}
    $sourceNames = @{}
    foreach ($item in $stage.Entries) {
        $sourcePath = [System.IO.Path]::GetFullPath(
            (Join-Path $moduleRoot $item.Source)
        )
        if (-not $sourcePath.StartsWith(
            $modulePrefix,
            [System.StringComparison]::OrdinalIgnoreCase
        )) {
            throw "Release source escapes module root: $($item.Source)"
        }
        if (-not (Test-Path -LiteralPath $sourcePath -PathType Leaf)) {
            throw "Required release source is missing: $sourcePath"
        }
        if ($sourceNames.ContainsKey($sourcePath)) {
            throw "Duplicate source in $($stage.Name): $($item.Source)"
        }
        $sourceNames[$sourcePath] = $true

        $entryName = $item.Entry.Replace("\", "/")
        if (
            $entryName -ne $item.Entry -or
            $entryName.StartsWith("/") -or
            $entryName.EndsWith("/") -or
            $entryName -match '(^|/)\.\.(/|$)'
        ) {
            throw "Unsafe ZIP entry in $($stage.Name): $($item.Entry)"
        }
        if ($entryNames.ContainsKey($entryName)) {
            throw "Duplicate ZIP entry in $($stage.Name): $entryName"
        }
        $entryNames[$entryName] = $true
    }
}

New-Item -ItemType Directory -Force -Path $distDirectory | Out-Null
$createdArchives = @()
$createdHashes = @()

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
                $zipEntry.LastWriteTime = $fixedEntryTimestamp
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

            $readStream = $null
            $readArchive = $null
            try {
                $readStream = [System.IO.File]::OpenRead($temporaryPath)
                $readArchive = New-Object System.IO.Compression.ZipArchive(
                    $readStream,
                    [System.IO.Compression.ZipArchiveMode]::Read,
                    $false
                )
                if ($readArchive.Entries.Count -ne $stage.Entries.Count) {
                    throw "ZIP entry-count verification failed for $($stage.Name)."
                }
                foreach ($item in $stage.Entries) {
                    $verifiedEntry = $readArchive.GetEntry($item.Entry)
                    if ($null -eq $verifiedEntry) {
                        throw "ZIP entry verification failed: $($item.Entry)"
                    }
                    $sourceLength = (Get-Item -LiteralPath (
                        Join-Path $moduleRoot $item.Source
                    )).Length
                    if ($verifiedEntry.Length -ne $sourceLength) {
                        throw "ZIP length verification failed: $($item.Entry)"
                    }
                }
            } finally {
                if ($null -ne $readArchive) {
                    $readArchive.Dispose()
                }
                if ($null -ne $readStream) {
                    $readStream.Dispose()
                }
            }

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

    $createdHashes = @(
        foreach ($archivePath in $createdArchives) {
            Get-FileHash -LiteralPath $archivePath -Algorithm SHA256
        }
    )
} catch {
    foreach ($createdArchive in $createdArchives) {
        if (Test-Path -LiteralPath $createdArchive) {
            Remove-Item -LiteralPath $createdArchive -Force
        }
    }
    throw
}

$createdHashes | Select-Object Path, Hash
