
pos_cnt=0
neg_cnt=0
for((i =1; i < 200;i++))
do
./iHog data/pos/image0/img_$i.pgm -h 2
OP_RET=$?
#echo $OP_RET
if [[ "$OP_RET" -eq "0" ]];then
	((pos_cnt++))
else
	let neg_cnt+=1
fi

done
let total=pos_cnt+neg_cnt

echo "detected: $pos_cnt failed: $neg_cnt total: $total"

:<<!
for((i =10; i < 100; i+= 2))
do
./iHog ppm/00$i.pgm
done
for((i =100; i < 900; i+=2))
do
./iHogSvm ppm/0$i.pgm
done


for((i =1000; i < 2000; i+=2))
do
./iHog ppm/$i.pgm
done

for((i =2000; i < 2350; i+=2))
do
./iHog ppm/$i.pgm
done
for((i =2000; i < 2350; i+=2))
do
./iHog ppm/0252.pgm
done
!
