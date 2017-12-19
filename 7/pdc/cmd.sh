cd $HADOOP_PREFIX

# bin/hdfs dfs -cat output/*

bin/hadoop dfs -copyFromLocal /downloads/pdc/input /join-input

bin/hadoop jar /usr/local/hadoop-2.7.1/share/hadoop/tools/lib/hadoop-streaming-2.7.1.jar \
    -file /downloads/pdc/mapper.py    -mapper /downloads/pdc/mapper.py   \
    -file /downloads/pdc/reducer.py   -reducer /downloads/pdc/reducer.py \
    -input /join-input/* -output /join-output

bin/hadoop dfs -cat /join-output/*