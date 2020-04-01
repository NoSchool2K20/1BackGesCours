# 1BackGesCours

Run those commands to use it :

```sh
npm install

npm run db:create

npm start
```

The server is available on the port 8080

# Via docker
```sh
docker-compose up -d 
```

This command line build and run the project on docker vm and expose the port 8080

# Deploy

Download the pem key (ask to the administrator to the project)
In the `deploy-serv.sh`, replace `<path_to_pem>` with your own path to the pem key

Use command
```sh
./deploy-serv.sh
```

# Url 

The preprod url is `http://18.220.58.155:8080` 

All url available: 
```sh
GET /                                     |  Welcome route
GET cours                                 |  Get all cours
GET module                                |  Get all module
```