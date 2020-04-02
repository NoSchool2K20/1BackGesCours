# 1BackGesCours

Run those commands to use it :

```sh
npm install

npm run build

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

# Url & Routes

The preprod url is `http://18.220.58.155:8080` 

## /parcours  
  
The parcours entity is made of a title and a description.
  
| **HTTP METHOD** | **PARAMS** | **BODY** | 
|------------|----------| -----| 
| *GET* | X | X    
| *POST* | X | `"title": "MIAGE",`<br>`"description": "description du parcours MIAGE"`

## /module

The module entity is made of a title and a description. We also need the refered parcours and the level of the module to know which module is the highest of the parcours

| **HTTP METHOD** | **PARAMS** | **BODY** | 
|------------|----------| -----| 
| *GET* | `parcours = <Nom du parcours>` | X    
| *POST* | X | `"title": "Licence 3 MIAGE",`<br>`"description": "description de la L3 MIAGE",`<br>`"parcours": "MIAGE"`,<br>`"niveau" : 1`

## /cours

The cours entity is made of a title, a description and the URL of the video of the class. We also need the module of which the class is part of.

| **HTTP METHOD** | **PARAMS** | **BODY** | 
|------------|----------| -----| 
| *GET* | `module = <Nom du module>` | X    
| *POST* | X | `"title": "POO",`<br>`"description": "description du cours de POO",`<br>`"video_url": "http://video.fr",`<br>`"modules": "Licence 3 MIAGE"`
