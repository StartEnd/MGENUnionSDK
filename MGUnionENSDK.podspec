#
# Be sure to run `pod lib lint MGUnionENSDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'MGUnionENSDK'
  s.version          = '0.2.8'
  s.summary          = '微游戏海外联运SDK'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/StartEnd/MGENUnionSDK'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'Mr.Song' => '996982027@qq.com' }
  s.source           = { :git => 'https://github.com/StartEnd/MGENUnionSDK.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '9.0'
  s.pod_target_xcconfig = {'GCC_PREPROCESSOR_DEFINITIONS' => '$(inherited) MGUNIONENSDKCOCOAPODS=1' }
  s.user_target_xcconfig = {'GCC_PREPROCESSOR_DEFINITIONS' => '$(inherited) MGUNIONENSDKCOCOAPODS=1' }
  
  # 依赖的自己的Framework
  s.vendored_frameworks = 'MGUnionENSDK/MGUnionENSDK.framework'
  s.resources = 'MGUnionENSDK/MGUnionENSDKReso.bundle'
  # s.source_files = 'MGUnionENSDK/Classes/**/*'

  s.public_header_files = 'Pod/Classes/**/*.h'
  # s.frameworks = 'UIKit', 'Foundation'
  # s.dependency 'AFNetworking', '~> 2.3'
  
  s.dependency 'AppsFlyerFramework'
  s.dependency 'FBSDKCoreKit'
  s.dependency 'FBSDKLoginKit'
  s.dependency 'FBSDKShareKit'
  s.dependency 'FBSDKPlacesKit'
  s.dependency 'SVProgressHUD'
  s.dependency 'Masonry'
  
end
