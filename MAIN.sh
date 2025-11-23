#!/bin/bash
#This is the main script to run
#It calls the subscripts then exits 0 if all went well, else it exits 1

Add_User(){	 #takes firstName and Lastname, anything else is weird.
	UserName="$1.$2"
	UserPassword="$1$2DEELTECH" 
	echo "$UserName $UserPassword" >> "UserList.txt" #Comment this line out on release version
<<CommentBlock
	This actually adds the user to the system, blocked it out on this version, bc, well, this isnt being run in a vm, tested it though with my name and I know it works
	sudo adduser --disabled-password --allow-bad-names --gecos "" "$UserName"
	echo "$UserName:$UserPassword" | sudo chpasswd
	echo "User '$USERNAME' created successfully."	
CommentBlock
}	

echo "" > "UserList.txt" #Comment this out in release version
chmod +x "liscenceVerifier.sh"
chmod +x "Parser.sh"
#Im bad with bash. Let me tell you how much I hate bash.. I HATE BASH. STUPID SYNTAX. I MADE THIS WHOLE PROGRAM AND I HATE BASH.
Return_Value="$(./liscenceVerifier.sh)"
if(( Return_Value == 1 )); then
	echo "Liscence NOT verified, please killyourself"
else
	echo "Liscence verified, proceeding"
fi
FirstName=0
LastName=0
#The Main Menu
response=0
echo "Hello and welcome to the DEELTECH user parser and account creator!"
while true; do

	echo "Please Press 1 for normal account creation procedure, or 2 to add a user manually"
	read response
	if(( response  == 1 )); then
		./Parser.sh
		while read w1 w2; do
		Add_User $w1 $w2
		done < names.txt

		break
	fi
	if(( response == 2 )); then
		echo "First Name?"
		read FirstName
		echo "Last Name?"
		read LastName
		Add_User $FirstName $LastName
		break
	fi
done
rm names.txt thepage.txt
exit 0 
