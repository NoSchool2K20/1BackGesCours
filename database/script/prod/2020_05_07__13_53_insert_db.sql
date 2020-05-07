INSERT INTO qsi.parcours(title, description) VALUES ('Analyste Cyberdefense', 'Le Master Cyberdefense est destine a des ingenieurs en informatique qui desirent devenir des specialistes de haut niveau en securite des systemes d’information.');
INSERT INTO qsi.parcours(title, description) VALUES ('Developpeur Fullstack', 'La formation de developpement d''application full stack vise a former des personnes au metier de developpeur web, front-end et back-end.');

INSERT INTO qsi.module(title, description) VALUES ('Master 1 AC', 'Le Master 1 est la premiere annee pour l''obtention du diplôme, elle donne les connaissances de base sur la cybersecurite.');
INSERT INTO qsi.module(title, description) VALUES ('Master 2 AC', 'Le Master 2 est la derniere annee pour l''obtention du diplôme, elle consolide les connaissances sur la cybersecurite et se termine par un stage en entreprise.');
INSERT INTO qsi.module(title, description) VALUES ('Master 1 DF', 'Le Master 1 est la premiere annee pour l''obtention du diplôme, elle approndit les connaissances en developpement et competences humaines.');
INSERT INTO qsi.module(title, description) VALUES ('Master 2 DF', 'Le Master 2 est la derniere annee pour l''obtention du diplôme, elle consolide les connaissances en developpement et se termine par un stage en entreprise.');

INSERT INTO qsi.parcours_module(parcours, module, niveau) VALUES ('Analyste Cyberdefense', 'Master 1 AC', 1); 
INSERT INTO qsi.parcours_module(parcours, module, niveau) VALUES ('Analyste Cyberdefense', 'Master 2 AC', 2); 
INSERT INTO qsi.parcours_module(parcours, module, niveau) VALUES ('Developpeur Fullstack', 'Master 1 DF', 1);
INSERT INTO qsi.parcours_module(parcours, module, niveau) VALUES ('Developpeur Fullstack', 'Master 2 DF', 2);

