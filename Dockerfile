FROM node:13
COPY lib /

CMD ["node", "/js/src/Index.bs.js"] 