# 1BackGesCours

Run those commands to use it :

```sh
npm install

npm run build

npm start
```

The server is available on the port 8080

#For the dev

create and fill the DB 

```
docker-compose up -d qsi-db
docker exec -it <CONTAINER ID> mysql -u root -proot -e "$(cat script/create_db.sql)"
```

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

The prod url is `http://18.220.58.155:8080` 
The pré-prod url is `http://35.180.174.135:8080`

For each route to call, you need to put your user token in the header of the request

## Hierarchie of role 

We have 3 differents roles
 - Etudiant
 - Professeur 
 - Administrateur

And more
 - an Administrateur can do everything that a Professeur and Etudiant can do
 - a Professeur can do everything that an Etudiant can do
 - an Etudiant is the basic role of our application
 
## /parcours  
  
The parcours entity is made of a title and a description.
  
| **HTTP METHOD** | **HEADER** | **PARAMS** | **BODY** | **MINIMAL_ROLE** |
|------------|---------|-------| -----| -----| 
| *GET* | Authorization : Bearer -token- | X | X | Etudiant
| *POST* | Authorization : Bearer -token- | X | `"title": "MIAGE",`<br>`"description": "description du parcours MIAGE"` | Administrateur

## /module

The module entity is made of a title and a description. We also need the refered parcours and the level of the module to know which module is the highest of the parcours

| **HTTP METHOD** | **HEADER** | **PARAMS** | **BODY** | **MINIMAL_ROLE** |
|------------|---------|-------| -----| -----|
| *GET* | Authorization : Bearer -token- | `parcours = <Nom du parcours>` | X | Etudiant
| *POST* | Authorization : Bearer -token- | X | `"title": "Licence 3 MIAGE",`<br>`"description": "description de la L3 MIAGE",`<br>`"parcours": "MIAGE"`,<br>`"niveau" : 1` | Administrateur

## /cours

The cours entity is made of a title, a description and the URL of the video of the class. We also need the module of which the class is part of.

| **HTTP METHOD** | **HEADER** | **PARAMS** | **BODY** | **MINIMAL_ROLE** |
|------------|---------|-------| -----| -----| 
| *GET* | Authorization : Bearer -token- | `module = <Nom du module>`  <br><br>  `title = <titre a filtrer>` | X | Étudiant
| *POST* | Authorization : Bearer token- | X | `"title": "POO",`<br>`"description": "description du cours de POO",`<br>`"video_url": "http://video.fr",`<br>`"modules": "Licence 3 MIAGE"` | Professeur
