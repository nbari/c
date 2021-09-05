https://github.com/redis/redis/pull/7179/files

in redis.conf:

    server_cpulist 0-40:2
    bio_cpulist 1-40:2
    aof_rewrite_cpulist 1-40:2
    bgsave_cpulist 1-40:2


To compile:

    clang cpuset.c -o x

Test your input:

       setcpuaffinity("0-20:2");
