def conan_channel = (env.BRANCH_NAME == "master") ? "sdk/stable" : "sdk/testing"

pipeline {
  agent none
  options {
    timeout(time: 1, unit: 'HOURS')
  }
  stages {
    stage ('Matrix Build') {
      matrix {
        axes {
          axis {
            name 'docker_image'
            values 'sdk/conan-android-armv7:latest', 'sdk/conan-centos7-gcc7-x86_64:latest', 'sdk/conan-centos7-clang5-x86_64-sanitize_address:1.0.4'
          }
          axis {
            name 'conan_options'
            values ' '
          }
        }
        stages {
          stage('Conan Build') {
            environment {
              CONAN_REMOTE_CREDS = credentials('sdk-jenkins-sdk-builder-on-artifactory')
              CONAN_LOGIN_USERNAME = "${env.CONAN_REMOTE_CREDS_USR}"
              CONAN_PASSWORD = "${env.CONAN_REMOTE_CREDS_PSW}"
            }
            agent {
              docker {
                label 'sdk-docker'
                image '${docker_image}'
                registryUrl 'http://registry.ba.innovatrics.net/'
                args '-u root --privileged'
              }
            }
            stages {
              stage('Conan Create') {
                steps {
                  sh """
                    conan create . ${conan_channel} ${conan_options} -u -b outdated -pr docker-default
                  """
                }
              }
              stage('Conan Upload') {
                when { anyOf { branch 'dev'; branch 'master' } }
                steps {
                  sh """
                    conan upload  "*" --all --confirm --remote sdk --retry 3 --retry-wait 10 --parallel
                    """
                }
              }
            }
          }
        }
      }
    }
  }
}
