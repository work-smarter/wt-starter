pipeline {
  agent any
  environment {
    AWS_ACCESS_KEY_ID = credentials('AWS_ACCESS_KEY_ID')
    AWS_SECRET_ACCESS_KEY = credentials('AWS_SECRET_ACCESS_KEY')
    AWS_REGION = credentials('AWS_REGION')
    WT_CPONFIG_FILE_PATH = credentials('WT_STARTER_CONFIG_FILE')
  }
  stages {
    stage('build') {
      steps {
        sh 'chmod +x scripts/docker_builder_images.sh'
        // sh 'rm -f ./wt_config.xml'
        sh 'cp $WT_CPONFIG_FILE_PATH ./wt_config.xml'
        // sh 'echo $WT_CPONFIG_FILE_PATH > wt_config_path.txt'
        sh 'cat wt_config.xml'
        sh 'scripts/docker_builder_images.sh'
      }
    }
    
    stage('deploy') {
      steps {
        sh 'chmod +x scripts/docker_deploy.sh'
        sh 'scripts/docker_deploy.sh $AWS_ACCESS_KEY_ID $AWS_SECRET_ACCESS_KEY $AWS_REGION'
      }
    }
  }
}
