/**************************** la customisacion ****************************/
def _conan_package_name = "ansi_iso_accuracy_test"
def _conan_channel = (env.BRANCH_NAME =~ /master/) ?  "tpd/stable" : "tpd/testing"
def _conan_remote_name = "sdk"

/**************************** windows build steps definitions ****************************/
def _conan_create_script_bat = """
@echo on
call "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\BuildTools\\VC\\Auxiliary\\Build\\vcvarsall.bat" %VCVARS_ARCH%

conan config install ssh://git@git.ba.innovatrics.net:7999/sdk/innovatrics-conan-config.git

conan create --remote ${_conan_remote_name} \
             --update \
             --profile %CONAN_PROFILE% \
             --build outdated \
             --build ${_conan_package_name} \
             . ${_conan_channel}
"""

def _conan_upload_script_bat = """
@echo on
SET CONAN_LOGIN_USERNAME="%CONAN_REMOTE_CREDS_USR%"
SET CONAN_PASSWORD="%CONAN_REMOTE_CREDS_PSW%"

conan user --clean
conan user -r sdk -p "%CONAN_REMOTE_CREDS_PSW%" "%CONAN_REMOTE_CREDS_USR%"
conan upload --remote ${_conan_remote_name} --all --force --confirm ${_conan_package_name}/*@${_conan_channel}
"""

/**************************** linux/unix build steps definitions ****************************/

def _conan_create_script_sh = """#!/bin/bash -e
set -x
conan config install

conan create --remote ${_conan_remote_name} \
             --update \
             --profile \$CONAN_PROFILE \
             --build outdated \
             --build ${_conan_package_name} \
             .  ${_conan_channel}
"""

def _conan_upload_script_sh = """#!/bin/bash -e
set -x
CONAN_LOGIN_USERNAME="\$CONAN_REMOTE_CREDS_USR" \
CONAN_PASSWORD="\$CONAN_REMOTE_CREDS_PSW" \
conan upload --remote ${_conan_remote_name} --all --force --confirm '*'
"""

/**************************** la pipelina ****************************/

pipeline {
    agent none
    options {
        timestamps()
        timeout(time: 1, unit: 'HOURS')
    }
    stages {
        stage ('Build') {
            parallel {
                stage ('Windows Visual Studio 2017 x64') {
                    environment {
                        CONAN_REMOTE_CREDS = credentials('sdk-jenkins-sdk-builder-on-artifactory')
                        CONAN_PROFILE = 'innovatrics-msvc-2017'
                        VCVARS_ARCH = 'x64'
                    }
                    agent {
                        label 'windows'
                    }
                    stages {
                        stage('Conan create') {
                            steps {
                                bat _conan_create_script_bat
                            }
                        }
                        stage('Conan upload') {
                            when {
                                anyOf {
                                    branch 'dev'; branch 'master'
                                }
                            }
                            steps {
                                bat _conan_upload_script_bat
                            }
                        }
                    }
                }
                stage ('Windows Visual Studio 2017 Win32') {
                    environment {
                        CONAN_REMOTE_CREDS = credentials('sdk-jenkins-sdk-builder-on-artifactory')
                        CONAN_PROFILE = 'innovatrics-msvc-2017-x86'
                        VCVARS_ARCH = 'x86'
                    }
                    agent {
                        label 'windows'
                    }
                    stages {
                        stage('Conan create') {
                            steps {
                                bat _conan_create_script_bat
                            }
                        }
                        stage('Conan upload') {
                            when {
                                anyOf {
                                    branch 'dev'; branch 'master'
                                }
                            }
                            steps {
                                bat _conan_upload_script_bat
                            }
                        }
                    }
                }
                stage ('Linux Intel 18') {
                    environment {
                        CONAN_REMOTE_CREDS = credentials('sdk-jenkins-sdk-builder-on-artifactory')
                        CONAN_PROFILE = 'innovatrics-intel-18'
                    }
                    agent {
                        docker {
                            label 'sdk-docker'
                            image 'sdk/conan-centos7-intel18:latest'
                            registryUrl 'http://registry.ba.innovatrics.net/'
                            args  '-u root --privileged'
                        }
                    }
                    stages {
                        stage('Conan create') {
                            steps {
                                sh _conan_create_script_sh
                            }
                        }
                        stage('Conan upload') {
                            when {
                                anyOf {
                                    branch 'dev'; branch 'master'
                                }
                            }
                            steps {
                                sh _conan_upload_script_sh
                            }
                        }
                    }
                }
                stage ('Linux GCC 7') {
                    environment {
                        CONAN_REMOTE_CREDS = credentials('sdk-jenkins-sdk-builder-on-artifactory')
                        CONAN_PROFILE = 'innovatrics-gcc-7'
                    }
                    agent {
                        docker {
                            label 'sdk-docker'
                            image 'sdk/conan-centos7-gcc7:latest'
                            registryUrl 'http://registry.ba.innovatrics.net/'
                            args  '-u root --privileged'
                        }
                    }
                    stages {
                        stage('Conan create') {
                            steps {
                                sh _conan_create_script_sh
                            }
                        }
                        stage('Conan upload') {
                            when {
                                anyOf {
                                    branch 'dev'; branch 'master'
                                }
                            }
                            steps {
                                sh _conan_upload_script_sh
                            }
                        }
                    }
                }
            }
        }
    }
}
