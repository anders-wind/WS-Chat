FROM node:alpine as builder
# Global dependencies
RUN apk update && apk upgrade && \
    apk add --no-cache bash git openssh

WORKDIR /app
# App dependencies

# Install Dependencies
COPY ./package*.json ./
RUN yarn install

# Build app
COPY . .
RUN npm run build

# Runtime image
FROM nginx:alpine
COPY default.conf /etc/nginx/conf.d/default.conf
COPY --from=builder /app/dist /usr/share/nginx/html/