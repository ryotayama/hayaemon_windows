Copy-Item ./nezplug++/npnez.txt ./nezplug++/npnez.def -Force
$data=Get-Content .\nezplug++\npnez.def
for($i = 0; $i -lt 226; $i++){
	if(($i -lt 4) -Or (49 -lt $i))
	{
		$data[$i] = $null
	}
}
$data | Out-File ./nezplug++/npnez.def -Encoding UTF8
