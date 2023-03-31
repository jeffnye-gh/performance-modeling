
# Kaggle download

This directory is a temp for data from kaggle.

The zip'd file is ++250MB, so it is not stored in git.
Note: the 6 uncompressed files are ~750MB each.

## Kaggle setup

### Install kaggle python support

    - sudo pip3 install kaggle

### Retrieve your Kaggle auth json file

    - Create/login to kaggle account
    - click icon/picture upper right
    - click account
    - scroll to api
    - create new api token
    - copy this file to ~/.kaggle
    - set permissions as you wish

### Down load data

    - with auth json in place:
    - kaggle datasets download -d dmitryshkadarevich/branch-prediction

### Unzip

    - unzip branch-prediction.zip
