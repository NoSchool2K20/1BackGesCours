FROM node:13

WORKDIR /usr/src/app

COPY package*.json ./

RUN npm Install

COPY . .

EXPOSE 9000

CMD ["npm", "start"] 