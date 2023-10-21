# Title : Write a program to implement an address book with options given below: a) Create address book. b) View address book. c) Insert a record. d) Delete a record. e) Modify a record. f) Exit 
# Code:

ch=1
while [ $ch -ne 7 ]
do
	echo -e "\nEnter the choise to perform operation on Address Book "
	echo -e "1.Create Address Book \n2.Insert a Record \n3.Modify a record \n4.View Address Book \n5.Search Record in Address Book  \n6.Delete a Record  \n7.Exit"
	read ch
	case $ch in
	1)
		echo "Enter the file name"
		read filename
		touch $filename
		echo "Address Book Name $filename Created"
	;;
	
	2)
		if [ -f $filename ]
		then
			echo "Enter the Name of Person"
			read pname
			echo "Enter the Person ID"
			read pid
			echo "Enter the City Name"
			read pcity
			while [ True ]
			do
				echo "Enter the Mobile No."
				read pmob
				if [ ${#pmob} -eq 10 ]
				then
					break
				else
					echo "Enter The valid 10 Digit Mobile No."
				fi
			done

			echo -e "$pname\t$pid\t$pcity\t$pmob" >> $filename
		fi
	;;
	
	3)
		if [ -f $filename ]
		then
			echo -e "\n1.Modify the specific Record \n2.Modify all the Record"
			read ch1
			case $ch1 in
			1)
				echo -e "Enter the Person Id to get Record Line Number"
				read pidrecord
				lineno=$(grep -n $pidrecord $filename | cut -d ":" -f1)
				echo -e "Which field You Want to modify \n1.Person Name \n2.Person ID \n3.City \n4.Mobile No."
				read ch2
				case $ch2 in
				1)
					echo -e "\nEnter name of person"
					read pname
					echo -e "\nEnter Name to Modify"
					read pnamepatt
					sed -i "${lineno} s/$pname/$pnamepatt/" $filename
				;;
				
				2)
					echo -e "\nEnter ID of person"
					read pid
					echo -e "\nEnter ID to Modify"
					read pidpatt
					sed -i "${lineno} s/$pid/$pidpatt/" $filename
				;;
				
				3)
					echo -e "\nEnter city of person"
					read pcity
					echo -e "\nEnter City to Modify"
					read pcitypatt
					sed -i "${lineno} s/$pcity/$pcitypatt/" $filename
				;;
				
				4)
					echo -e "\nEnter mobile no. of person"
					read pmob
					echo -e "\nEnter Mobile No. to Modify"
					read pmobpatt
					sed -i "${lineno} s/$pmob/$pmobpatt/" $filename
				;;
				
				esac
			;;
			
			2)
				echo -e "\nEnter the Old String"
				read patternold
				echo -e "\nEnter the New String"
				read patternnew
				sed -i 's/'$patternold'/'$patternnew'/' $filename			
			;;

			esac

		else
			echo "File Does not Exist"
		fi	
	;;
	
	4)
		if [ -f $filename ]
		then
			cat $filename
		else
			echo "File Does not Exist"
		fi
	;;
	
	5)
		if [ -f $filename ]
		then
			echo -e "Enter the Person ID to search record"
			read pidpatt
			grep $pidpatt $filename
		else
			echo "File Does not Exist"
		fi
	;;
	
	6)
		if [ -f $filename ]
		then
			echo -e "Enter the Person ID to delete record"
			read pidpatt
			echo "Record deleted sucessfully"
			grep $pidpatt $filename
			sed -i '/'$pidpatt'/d' $filename
		else
			echo "File Does not Exist"
		fi
	;;
	
	7)
		echo -e "\nProgram Ended" 
	;;
	esac
done


# Output :
# pranav@LAPTOP-TB69H925:~$ cd OS
# pranav@LAPTOP-TB69H925:~/OS$ ./addbook.sh

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 1
# Enter the file name
# addbook.txt
# Address Book Name addbook.txt Created

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 2
# Enter the Name of Person
# Pranav
# Enter the Person ID
# t21032
# Enter the City Name
# jarud
# Enter the Mobile No.
# 12334
# Enter The valid 10 Digit Mobile No.
# Enter the Mobile No.
# 1234567890

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 2
# Enter the Name of Person
# Abhi
# Enter the Person ID
# T21033
# Enter the City Name
# jarud
# Enter the Mobile No.
# 7492848382

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 2
# Enter the Name of Person
# Mohak
# Enter the Person ID
# T21001
# Enter the City Name
# Nashik
# Enter the Mobile No.
# 8563748283

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 2
# Enter the Name of Person
# Deep
# Enter the Person ID
# t21029
# Enter the City Name
# jalgaon
# Enter the Mobile No.
# 8452693847

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 2
# Enter the Name of Person
# Aditya
# Enter the Person ID
# t21055
# Enter the City Name
# CSMN
# Enter the Mobile No.
# 5674728458

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 4
# Pranav  t21032  jarud   1234567890
# Abhi    T21033  jarud   7492848382
# Mohak   T21001  Nashik  8563748283
# Deep    t21029  jalgaon 8452693847
# Aditya  t21055  CSMN    5674728458

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 3

# 1.Modify the specific Record
# 2.Modify all the Record
# 1
# Enter the Person Id to get Record Line Number
# T21033
# Which field You Want to modify
# 1.Person Name
# 2.Person ID
# 3.City
# 4.Mobile No.
# 1

# Enter name of person
# Abhi

# Enter Name to Modify
# Abhijit

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 4
# Pranav  t21032  jarud   1234567890
# Abhijit T21033  jarud   7492848382
# Mohak   T21001  Nashik  8563748283
# Deep    t21029  jalgaon 8452693847
# Aditya  t21055  CSMN    5674728458

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 3

# 1.Modify the specific Record
# 2.Modify all the Record
# 2

# Enter the Old String
# jarud

# Enter the New String
# Warud

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 4
# Pranav  t21032  Warud   1234567890
# Abhijit T21033  Warud   7492848382
# Mohak   T21001  Nashik  8563748283
# Deep    t21029  jalgaon 8452693847
# Aditya  t21055  CSMN    5674728458

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 5
# Enter the Person ID to search record
# t21029
# Deep    t21029  jalgaon 8452693847

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 6
# Enter the Person ID to delete record
# T21033
# Record deleted sucessfully
# Abhijit T21033  Warud   7492848382

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 4
# Pranav  t21032  Warud   1234567890
# Mohak   T21001  Nashik  8563748283
# Deep    t21029  jalgaon 8452693847
# Aditya  t21055  CSMN    5674728458

# Enter the choise to perform operation on Address Book
# 1.Create Address Book
# 2.Insert a Record
# 3.Modify a record
# 4.View Address Book
# 5.Search Record in Address Book
# 6.Delete a Record
# 7.Exit
# 7

# Program Ended
# pranav@LAPTOP-TB69H925:~/OS$