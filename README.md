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

#Routes

## /parcours  
  
| **HTTP METHOD** | **PARAMS** | **BODY** | 
|------------|----------| -----| 
| *GET* | X | X    
| *POST* | X | `"title": "MIAGE",`<br>`"description": "description du parcours MIAGE"`

## /module
| **HTTP METHOD** | **PARAMS** | **BODY** | 
|------------|----------| -----| 
| *GET* | `parcours = <Nom du parcours>` | X    
| *POST* | X | `"title": "Licence 3 MIAGE",`<br>`"description": "description de la L3 MIAGE",`<br>`"parcours": "MIAGE"`,<br>`"niveau" : 1`

## / cours
| **HTTP METHOD** | **PARAMS** | **BODY** | 
|------------|----------| -----| 
| *GET* | `module = <Nom du module>` | X    
| *POST* | X | `"title": "POO",`<br>`"description": "description du cours de POO",`<br>`"video_url": "http://video.fr",`<br>`"modules": "Licence 3 MIAGE"`
