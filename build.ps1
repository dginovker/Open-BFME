$ErrorActionPreference = "Stop"

if ($args.Count -ne 0) {
    Write-Error "build.ps1 does not take arguments yet."
    exit 2
}

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$Python = Get-Command py -ErrorAction SilentlyContinue

if ($Python) {
    & py -3 "$ScriptDir\tools\build.py"
} else {
    & python "$ScriptDir\tools\build.py"
}
