pipeline {
  agent any
  stages {
    stage('build') {
      steps {
        sh 'chmod +x scripts/docker_builder_images.sh'
        sh 'scripts/docker_builder_images.sh'
      }
    }
    
    stage('deploy') {
      steps {
        sh 'chmod +x scripts/docker_deploy.sh'
        sh 'scripts/docker_deploy.sh'
      }
    }
  }
}
