make clean
mke
$src = "Target/Main.exe"
$dest = "C:\AchiorLabs\bin\C4C.exe"
New-Item -ItemType Directory -Path "C:\AchiorLabs\bin" -Force | Out-Null
Copy-Item $src $dest -Force
Write-Host "Installed C4C to $dest"
