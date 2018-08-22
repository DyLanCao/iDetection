
:<<!
for((i =0; i < 10;i++))
do
./iHog ppm/000$i.pgm
done

for((i =10; i < 100; i+= 2))
do
./iHog ppm/00$i.pgm
done
!

for((i =100; i < 900; i+=2))
do
./iHog ppm/0$i.pgm
done


for((i =1000; i < 2000; i+=2))
do
./iHog ppm/$i.pgm
done

for((i =2000; i < 2350; i+=2))
do
./iHog ppm/$i.pgm
done
