
#!/bin/bash
# var=0

# while ((var <= 100))
# do
#     echo "create $var.c successful"
#     touch $var.c
#     ((var++))
# done



i = 1
sum=0
while (( i <=100))
do
    ((sum+=i))
    ((i++))
done
echo “This sum is:$sum”