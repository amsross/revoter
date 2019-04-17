# revoter
cast your vote!

## env vars

* (string) `URL_BASE`
* (string) `URL_TOWN`
* (string) `URL_VOTE`
* (string) `AWS_ACCESS_KEY_ID`
* (string) `AWS_SECRET_ACCESS_KEY`
* (string) `DOMAIN`
* (string) `CERT`

## run locally

```
URL_BASE="" URL_TOWN="" URL_VOTE="" \
AWS_ACCESS_KEY_ID="" AWS_SECRET_ACCESS_KEY="" \
DOMAIN="" CERT="" \
npm run local
```

## deploy

```
URL_BASE="" URL_TOWN="" URL_VOTE="" \
AWS_ACCESS_KEY_ID="" AWS_SECRET_ACCESS_KEY="" \
DOMAIN="" CERT="" \
npm run deploy -- -v --stage [STAGE]
```
