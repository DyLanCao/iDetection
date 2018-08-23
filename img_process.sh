# 搞一个i的变量
i=1
num=7
#for f in $(find ./seg1 -iname "*.*"); 
for f in seg$num/*
do
	news=img_$i
	#echo $f
	((i++))
	echo $news.pgm
	convert $f -resize 320x240 $news.pgm
	mv $news.pgm image$num/
done
