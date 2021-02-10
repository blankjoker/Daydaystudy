
#!/bin/bash
var=0

# while ((var <= 1000))
while [ $var -lt 1000 ]
do
    echo "create $var.c successful"
    mkdir $var.c
    ((var++))
done



# i = 1
# sum=0
# while (( i <=100))
# do
# ((sum+=i))
# ((i++))
# done
 
# echo “This sum is:$sum”