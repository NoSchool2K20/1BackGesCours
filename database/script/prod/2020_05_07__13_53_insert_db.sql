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

INSERT INTO qsi.cours(title, description, video_url) VALUES ('Blockchain et crypto-monnaie : analyse et mise en oeuvre','Ce cours vise a expliquer les concepts de blockchain et crypto-monnaie, en insistant sur les differences entre ceux-ci.','https://www.youtube.com/embed/lr9sqK2PpnU');
INSERT INTO qsi.cours(title, description, video_url) VALUES ('Rappels mathematiques','Ce cours vise a rappeler et approfondir les notions mathematiques necessaires a la poursuite du programme.','https://www.youtube.com/embed/F6-qP8vvJYg');
INSERT INTO qsi.cours(title, description, video_url) VALUES ('Securite des reseaux et des systemes informatiques','Ce cours vise a consolider les connaissances en reseaux et systemes des etudiants.','https://www.youtube.com/embed/jGRkdzEd0PY');
INSERT INTO qsi.cours(title, description, video_url) VALUES ('Algorithmes et complexite','L''objectif du cours est de preparer les etudiants a repondre aux questions de conception, d''efficacite et de complexite. d''algorithmes.','https://www.youtube.com/embed/x1sFJ_HKEaI');
INSERT INTO qsi.cours(title, description, video_url) VALUES ('Technologies pour applications connectees','L''UE Technologies pour Applications Connectees (TAC) se concentre sur le developpement des applications connectees a Internet.','https://www.youtube.com/embed/_JNeiGbAgL4');

INSERT INTO qsi.module_cours(module, cours) VALUES ('Master 1 AC', 'Blockchain et crypto-monnaie : analyse et mise en oeuvre');
INSERT INTO qsi.module_cours(module, cours) VALUES ('Master 1 AC', 'Rappels mathematiques');
INSERT INTO qsi.module_cours(module, cours) VALUES ('Master 2 AC', 'Securite des reseaux et des systemes informatiques');
INSERT INTO qsi.module_cours(module, cours) VALUES ('Master 1 DF', 'Algorithmes et complexite');
INSERT INTO qsi.module_cours(module, cours) VALUES ('Master 2 DF', 'Technologies pour applications connectees');

