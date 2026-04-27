# Check if profile exists 
if (!(Test-Path $PROFILE)) 
{
    New-Item -ItemType File -Path $PROFILE -Force | Out-Null
}

# Marker to avoid duplicate insertion
$marker = "# >>> MSVC AUTO-LOAD >>>"

# Check if already added
if (Select-String -Path $PROFILE -Pattern $marker -Quiet) 
{
    Write-Host "MSVC auto-load already configured in profile."
    exit
}

# The following block will be added to the profile configuration
$msvcBlock = @"
$marker
# Auto-load MSVC environment
`$vswhere = "`${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
`$vsInstall = & `$vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath

if (`$vsInstall) 
{
    `$vcvars = Join-Path `$vsInstall "VC\Auxiliary\Build\vcvars64.bat"

    cmd /c "`"`"`$vcvars`"`" && set" | ForEach-Object 
    {
        if (`$_ -match "^(.*?)=(.*)$") 
	{
            Set-Item -Path "Env:`$(`$matches[1])" -Value `$matches[2]
bind = SUPER, exec, ags toggle app-launcher-$monitor
        }
    }
}
$env:INCLUDE += ";C:\AchiorLabs\C4"
# <<< MSVC AUTO-LOAD <<<
"@

# Append to profile
Add-Content -Path $PROFILE -Value $msvcBlock

Write-Host "MSVC auto-load has been added to your PowerShell profile."
Write-Host "Restart PowerShell to apply."
#This will enable msvc for the current powershell profile needed for the toolchain to work appropriately
## CREATE required directories
$WorkingDirectory = Get-Location
$dirs = @(
	"Target",
	"Objects",
	"Objects/Frontend/Lexer",
	"Objects/Frontend/AST",	
	"Objects/FrontEnd/Parser",
    	"Objects/FrontEnd/TreeWalker",
    	"Objects/FrontEnd/IdentifierResolution",
    	"Objects/FrontEnd/LoopLabelling",
    	"Objects/FrontEnd/TypeChecking",
    	"Objects/FrontEnd/Driver",
    	"Objects/CmdLine",
    	"Objects/C4COptions",
    	"Objects/Driver",
  	"Objects/Support",
   	"Objects/MiddleEnd/C",
    	"Objects/MiddleEnd/Driver"
	
)
foreach ($dir in $dirs) 
{
	$fullpath = Join-Path $WorkingDirectory $dir
	if (!(Test-Path $fullpath)) 
	{
		New-Item -ItemType Directory -Path $fullpath -Force | Out-Null
		Write-Host " [+] Created $dir"
	}
	else
	{
		Write-Host " [x] $dir Already exists"
	}
}
$GlobalInclude = "C:\AchiorLabs\C4"
New-Item -ItemType Directory -Path $GlobalInclude -Force | Out-Null
Copy-Item "Src/Support/Include/Types.h" "$globalIclude\Types.h" -Force
