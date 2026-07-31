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
        Name = "module_15_stage_a_initial_inquiry.zip"
        Entries = @(
            @{ Source = "release\stage_a_README.md"; Entry = "README.md" },
            @{ Source = "student\inquiry_prompt.md"; Entry = "inquiry_prompt.md" },
            @{ Source = "student\inquiry_prompt_linear.md"; Entry = "inquiry_prompt_linear.md" }
        )
    },
    @{
        Name = "module_15_stage_b_representation_pause.zip"
        Entries = @(
            @{ Source = "release\stage_b_README.md"; Entry = "README.md" },
            @{ Source = "student\representation_reveal.md"; Entry = "representation_reveal.md" },
            @{ Source = "student\cognitive_pause.md"; Entry = "cognitive_pause.md" },
            @{ Source = "student\vocabulary.md"; Entry = "vocabulary.md" }
        )
    },
    @{
        Name = "module_15_stage_c_investigation.zip"
        Entries = @(
            @{ Source = "release\stage_c_README.md"; Entry = "README.md" },
            @{ Source = "student\investigation_worksheet.md"; Entry = "investigation_worksheet.md" },
            @{ Source = "student\investigation_worksheet_linear.md"; Entry = "investigation_worksheet_linear.md" }
        )
    },
    @{
        Name = "module_15_stage_d_textbook_models.zip"
        Entries = @(
            @{ Source = "release\stage_d_README.md"; Entry = "README.md" },
            @{ Source = "student\textbook.md"; Entry = "textbook.md" },
            @{ Source = "diagrams\mst_models.md"; Entry = "diagrams/mst_models.md" }
        )
    },
    @{
        Name = "module_15_stage_e_lab.zip"
        Entries = @(
            @{ Source = "release\stage_e_README.md"; Entry = "README.md" },
            @{ Source = "student\lab.md"; Entry = "student/lab.md" },
            @{ Source = "student\evidence_template.md"; Entry = "student/evidence_template.md" },
            @{ Source = "student\rubric.md"; Entry = "student/rubric.md" },
            @{ Source = "student\mst_cycle_autopsy.md"; Entry = "student/mst_cycle_autopsy.md" },
            @{ Source = "release\student_code_README.md"; Entry = "code/README.md" },
            @{ Source = "release\student_build.ps1"; Entry = "code/build.ps1" },
            @{ Source = "release\student_Makefile"; Entry = "code/Makefile" },
            @{ Source = "code\include\dsu.h"; Entry = "code/include/dsu.h" },
            @{ Source = "code\include\undirected_edge_list.h"; Entry = "code/include/undirected_edge_list.h" },
            @{ Source = "code\include\prim_frontier.h"; Entry = "code/include/prim_frontier.h" },
            @{ Source = "code\include\minimum_spanning_forest.h"; Entry = "code/include/minimum_spanning_forest.h" },
            @{ Source = "code\starter\prim.c"; Entry = "code/starter/prim.c" },
            @{ Source = "code\starter\kruskal.c"; Entry = "code/starter/kruskal.c" },
            @{ Source = "code\support\dsu.c"; Entry = "code/support/dsu.c" },
            @{ Source = "code\support\undirected_edge_list.c"; Entry = "code/support/undirected_edge_list.c" },
            @{ Source = "code\support\prim_frontier.c"; Entry = "code/support/prim_frontier.c" },
            @{ Source = "code\support\mst_support.c"; Entry = "code/support/mst_support.c" },
            @{ Source = "code\tests\test_core.c"; Entry = "code/tests/test_core.c" },
            @{ Source = "code\tests\test_student.c"; Entry = "code/tests/test_student.c" },
            @{ Source = "code\autopsy\README.md"; Entry = "code/autopsy/README.md" },
            @{ Source = "code\autopsy\faulty_endpoint_cycle.c"; Entry = "code/autopsy/faulty_endpoint_cycle.c" }
        )
    }
)

$expectedStageCounts = @(3, 4, 3, 3, 22)
for ($index = 0; $index -lt $stages.Count; $index += 1) {
    if ($stages[$index].Entries.Count -ne $expectedStageCounts[$index]) {
        throw "Internal release-map count mismatch for $($stages[$index].Name)."
    }
}

$expectedSourceRelativePaths = @(
    "README.md",
    "diagrams\mst_models.md",
    "instructor\answer_key.md",
    "instructor\lesson_plan.md",
    "instructor\technical_notes.md",
    "student\cognitive_pause.md",
    "student\evidence_template.md",
    "student\inquiry_prompt.md",
    "student\inquiry_prompt_linear.md",
    "student\investigation_worksheet.md",
    "student\investigation_worksheet_linear.md",
    "student\lab.md",
    "student\mst_cycle_autopsy.md",
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
    "code\include\dsu.h",
    "code\include\minimum_spanning_forest.h",
    "code\include\prim_frontier.h",
    "code\include\undirected_edge_list.h",
    "code\starter\kruskal.c",
    "code\starter\prim.c",
    "code\solution\kruskal.c",
    "code\solution\prim.c",
    "code\support\dsu.c",
    "code\support\mst_support.c",
    "code\support\prim_frontier.c",
    "code\support\undirected_edge_list.c",
    "code\tests\test_core.c",
    "code\tests\test_extension.c",
    "code\tests\test_student.c",
    "code\autopsy\README.md",
    "code\autopsy\faulty_endpoint_cycle.c"
)

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
Source inventory does not match the required 47-file package:
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
    $sourceFiles.Count -ne 47 -or
    $markdownCount -ne 26 -or
    $powershellCount -ne 3 -or
    $makefiles.Count -ne 2 -or
    $cCount -ne 12 -or
    $headerCount -ne 4
) {
    throw @"
Source inventory must be exactly 47 files before dist:
26 Markdown, 3 PowerShell, 2 Makefiles, 12 C, and 4 headers.
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
    "graph",
    "vertex",
    "vertices",
    "edge",
    "weighted",
    "weight",
    "undirected",
    "directed",
    "adjacency",
    "edge list",
    "logical edge",
    "multigraph",
    "parallel edge",
    "self-loop",
    "self loop",
    "path",
    "spanning tree",
    "minimum spanning tree",
    "minimum spanning forest",
    "MST",
    "MSF",
    "tree",
    "forest",
    "component",
    "cycle",
    "acyclic",
    "Prim",
    "Kruskal",
    "algorithm",
    "frontier",
    "cut",
    "crossing edge",
    "safe edge",
    "key",
    "parent",
    "in_tree",
    "stale",
    "lazy duplicate",
    "Priority Queue",
    "PQ",
    "Heap",
    "Union-Find",
    "Union Find",
    "DSU",
    "disjoint set",
    "representative",
    "root",
    "DSU find",
    "find operation",
    "union",
    "path compression",
    "sort",
    "qsort",
    "comparator",
    "invariant",
    "validator",
    "certificate",
    "representation",
    "dense",
    "sparse",
    "complexity",
    "Big-O",
    "logarithm",
    "code",
    "C programming",
    "C language",
    "struct",
    "API",
    "TODO",
    "pseudocode",
    "status",
    "solution",
    "answer key",
    "instructor"
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

foreach ($stage in $stages) {
    $archivePath = Join-Path $distDirectory $stage.Name
    if (Test-Path -LiteralPath $archivePath) {
        throw "Refusing to overwrite existing archive: $archivePath"
    }

    $entryNames = @{}
    foreach ($item in $stage.Entries) {
        $sourcePath = Join-Path $moduleRoot $item.Source
        if (-not (Test-Path -LiteralPath $sourcePath -PathType Leaf)) {
            throw "Required release source is missing: $sourcePath"
        }
        if ($entryNames.ContainsKey($item.Entry)) {
            throw "Duplicate ZIP entry in $($stage.Name): $($item.Entry)"
        }
        $entryNames[$item.Entry] = $true
    }
}

New-Item -ItemType Directory -Force -Path $distDirectory | Out-Null
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
