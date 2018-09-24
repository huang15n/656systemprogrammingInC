 num=‘more $1 | wc -l‘
  i=1
  while [[ $i -le $num ]]; do
    for www in ‘head -$i $1 | tail -1‘; do
      if [[ $www == $2 ]]; then
www=$3 fi
      echo -n "$www " >> $4
    done
echo >> $4
    let "i = $i + 1"
  done