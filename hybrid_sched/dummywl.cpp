#include "include.h"
#include "dummywl.h"

void *dummy_work(void *data){
    struct thread_args *args = (struct thread_args *)data;
    unsigned int iter = 600000 * args->iter;
    int sum = 0;
    cpu_set_t cpuset;

    if(args->online){
        CPU_SET(args->cpus,&cpuset);
        if(!pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset)){
            std::cout<<"error in pthread_setaffinity_np\n";
            return;
        }
    }
    else{
        for(int i = 0; i < args->cpus; i++){
            CPU_SET(i,&cpuset);
        }
        if(!pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset)){
            std::cout<<"error in pthread_setaffinity_np\n";
            return;
        }
    }

    for(unsigned i = 0; i < iter; i++){
        sum += i;
    }
    return;
}

void *dummy_write(void *data){
    struct thread_args *args = (struct thread_args *)data;
    cpu_set_t cpuset;

    if(args->online){
        CPU_SET(args->cpus,&cpuset);
        if(!pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset)){
            std::cout<<"error in pthread_setaffinity_np\n";
            return;
        }
    }
    else{
        for(int i = 0; i < args->cpus; i++){
            CPU_SET(i,&cpuset);
        }
        if(!pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset)){
            std::cout<<"error in pthread_setaffinity_np\n";
            return;
        }
    }

    for(int i = 0; i < args->iter; i++){
        std::fstream dummyfile ("dummytext.txt");
        if (dummyfile.is_open())
        {            
            dummyfile << "Dummy workload.\n";            
            dummyfile.close();
        }
        else{
            std::cout << "Unable to open file";
            return;
        }
    }
    return;
}

void *dummy_read(void *data){
    struct thread_args *args = (struct thread_args *)data;
    std::string line;
    cpu_set_t cpuset;

    if(args->online){
        CPU_SET(args->cpus,&cpuset);
        if(!pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset)){
            std::cout<<"error in pthread_setaffinity_np\n";
            return;
        }
    }
    else{
        for(int i = 0; i < args->cpus; i++){
            CPU_SET(i,&cpuset);
        }
        if(!pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset)){
            std::cout<<"error in pthread_setaffinity_np\n";
            return;
        }
    }

    for(int i = 0; i < args->iter; i++){
        std::fstream dummyfile ("dummytext.txt");
        
        if (dummyfile.is_open())
        {        
            while(std::getline(dummyfile,line)){
                std::cout << line << '\n';
            }      
            dummyfile.close();
        }
        else{
            std::cout << "Unable to open file";
            return;
        }
    }
    return;
}

void *crawl_webpage(void *data){

    struct thread_args *args = (struct thread_args *)data;


    CkSpider spider;

    CkStringArray seenDomains;
    CkStringArray seedUrls;

    cpu_set_t cpuset;

    if(args->online){
        CPU_SET(args->cpus,&cpuset);
        if(!pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset)){
            std::cout<<"error in pthread_setaffinity_np\n";
            return;
        }
    }
    else{
        for(int i = 0; i < args->cpus; i++){
            CPU_SET(i,&cpuset);
        }
        if(!pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset)){
            std::cout<<"error in pthread_setaffinity_np\n";
            return;
        }
    }

    seenDomains.put_Unique(true);
    seedUrls.put_Unique(true);

    //  You will need to change the start URL to something else...
    seedUrls.Append("http://www.naver.com/");

    //  Set outbound URL exclude patterns
    //  URLs matching any of these patterns will not be added to the
    //  collection of outbound links.
    spider.AddAvoidOutboundLinkPattern("*?id=*");
    spider.AddAvoidOutboundLinkPattern("*.mypages.*");
    spider.AddAvoidOutboundLinkPattern("*.personal.*");
    spider.AddAvoidOutboundLinkPattern("*.comcast.*");
    spider.AddAvoidOutboundLinkPattern("*.aol.*");
    spider.AddAvoidOutboundLinkPattern("*~*");

    //  Use a cache so we don't have to re-fetch URLs previously fetched.
    spider.put_CacheDir("[somewhere]/hybrid_sched/spiderCache/");
    spider.put_FetchFromCache(true);
    spider.put_UpdateCache(true);

    while (seedUrls.get_Count() > 0) {

        const char *url = seedUrls.pop();
        spider.Initialize(url);

        //  Spider 5 URLs of this domain.
        //  but first, save the base domain in seenDomains
        const char *domain = spider.getUrlDomain(url);
        seenDomains.Append(spider.getBaseDomain(domain));

        int i;
        bool success;
        for (i = 0; i <= 4; i++) {
            success = spider.CrawlNext();
            if (success == true) {

                //  If the last URL was retrieved from cache,
                //  we won't wait.  Otherwise we'll wait 1 second
                //  before fetching the next URL.
                if (spider.get_LastFromCache() != true) {
                    spider.SleepMs(1000);
                }

            }
            else {
                //  cause the loop to exit..
                i = 999;
            }

        }

        //  Add the outbound links to seedUrls, except
        //  for the domains we've already seen.
        for (i = 0; i <= spider.get_NumOutboundLinks() - 1; i++) {

            url = spider.getOutboundLink(i);
            const char *domain = spider.getUrlDomain(url);
            const char *baseDomain = spider.getBaseDomain(domain);
            if (seenDomains.Contains(baseDomain) == false) {
                //  Don't let our list of seedUrls grow too large.
                if (seedUrls.get_Count() < 1000) {
                    seedUrls.Append(url);
                }

            }

        }

    }
}

void *dummy_sort(void *data){
    struct thread_args *args = (struct thread_args *)data;

    int size = 1000;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dis(0,1000);
    int iarr[size] = {0};
    cpu_set_t cpuset;

    if(args->online){
        CPU_SET(args->cpus,&cpuset);
        if(!pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset)){
            std::cout<<"error in pthread_setaffinity_np\n";
            return;
        }
    }
    else{
        for(int i = 0; i < args->cpus; i++){
            CPU_SET(i,&cpuset);
        }
        if(!pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset)){
            std::cout<<"error in pthread_setaffinity_np\n";
            return;
        }
    }

    for(int i = 0; i < args->iter; i++){
        for(int j = 0; j < size; j++){
            iarr[j] = dis(gen);
        }
        std::sort(iarr,iarr+size);
    }   
    return;
}