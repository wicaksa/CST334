#!/bin/bash

# Name: <Wicaksa Munajat>
# Date: <June 28, 2021> <DUE: June 29, 2021>
# Title: Lab1 - Unix/Linux Commands and Basic Shell Programming
# Description: This program computes the area of a rectange and the area of a circle. 

echo Executing $0
echo $(/bin/ls | wc -l)files 
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ "$user"="wicaksamunajat" ]
then
	echo "Now you can proceed!"
else
	echo "Check who logged in!"
fi

response="Yes"

# This loop will ask user to enter height and width of a rectangle.
# It will calculate the area of the rectangle and prompt user if they want to repeat.
while [ "$response" != "No" ]
do
	echo "Enter height of rectangle: "
	read height 
	echo "Enter width of rectangle: "
	read width
	area=`expr $height \* $width` 
	echo "The area of the rectangle is $area"

	echo "Would you like to repeat for another rectangle [Yes/No]?"
	read response
done

answer="Yes"

# This loop will ask user to enter radius of a circle and calculate its area.
while [ "$answer" != "No" ]
do
	pi=3.14
	echo "Enter the radius of a circle: "
	read rad
	areacircle=`echo $pi $rad $rad | awk '{print $1 * $2 * $3}'`  
	echo "The area of the circle is $areacircle"
	
	echo "Would you like to repeat for another circle [Yes/No]?"
	read answer
done

# Questions: What linux system are you using? Did you experience any difficulties with this lab task?
# I am using a MacOS as my linux system. Some of the problems with this lab included having extra spaces 
# after the equal sign (=) which led to the script not running. Justin helped me figure that bug out 
# during office hours. Another issue I had was figuring out the syntax of the awk. I figured out that 
# the variables go before the | and the arithmetic go after the | and the numbers just represent the 
# order of the variables put before the |.   
