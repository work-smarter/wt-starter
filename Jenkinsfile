pipeline {
  agent any
  environment {
    AWS_ACCESS_KEY_ID = credentials('AWS_ACCESS_KEY_ID')
    AWS_SECRET_ACCESS_KEY = credentials('AWS_SECRET_ACCESS_KEY')
    AWS_REGION = credentials('AWS_REGION')
    POSTGRES_PASSWORD = credentials('POSTGRES_PASSWORD')
    VPS_IP = credentials('VPS_IP')
    // WT_CONFIG_FILE = credentials('WT_STARTER_CONFIG_FILE')
  }
  stages {
    stage('build') {
      steps {
        // sh 'cp $WT_CONFIG_FILE ./wt_config.xml'
        sh 'chmod +x scripts/docker_builder_images.sh'
        sh 'scripts/docker_builder_images.sh || { echo "Deploy script failed"; exit 1; }'
      }
    }
    
    stage('deploy') {
      steps {
        sh 'chmod +x scripts/docker_deploy.sh'
        sh 'scripts/docker_deploy.sh $AWS_ACCESS_KEY_ID $AWS_SECRET_ACCESS_KEY $AWS_REGION $POSTGRES_PASSWORD $VPS_IP || { echo "Deploy script failed"; exit 1; } '
      }
    }
  }
}
