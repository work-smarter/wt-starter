pipeline {
  agent any
  stages {
    stage('build') {
      steps {
        echo 'Building wt_starter_build image'
        sh 'docker build -t wt_starter_build -f dockerfiles/Dockerfile_build .'
        sh 'docker build -t wt_starter -f dockerfiles/Dockerfile_deploy .'
      }
    }
    
    stage('deploy') {
      steps {
        echo 'Removing wt_starter container'
        sh 'docker rm -f wt_starter || true'
        echo 'Running wt_starter container'
        sh 'docker run --rm -d --network caddy -p 9010:9010 --name wt_starter wt_starter:latest'
      }
    }
  }
}
