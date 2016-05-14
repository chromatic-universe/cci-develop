<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='en' lang='en'>
<head>
<title>glib - Low level core library</title>
<meta name='generator' content='cgit v0.11.2'/>
<meta name='robots' content='index, nofollow'/>
<link rel='stylesheet' type='text/css' href='https://static.gnome.org/git.gnome.org/cgit-gnome.css'/>
<link rel='shortcut icon' href='https://static.gnome.org/img/logo/foot-16.png'/>
<link rel='alternate' title='Atom feed' href='https://git.gnome.org/browse/glib/atom/gio/tests/gdbus-example-server.c?h=master' type='application/atom+xml'/>
<link rel='vcs-git' href='git://git.gnome.org/glib' title='glib Git repository'/>
<link rel='vcs-git' href='https://git.gnome.org/browse/glib' title='glib Git repository'/>
<link rel='vcs-git' href='ssh://USERNAME@git.gnome.org/git/glib' title='glib Git repository'/>
</head>
<body>
<div id="global_domain_bar">
<div class="maxwidth">
	<div class="tab">
	<a class="root" href="https://www.gnome.org/">GNOME.org</a>
	</div>
</div>
</div>

<div id="page">
    <div id="logo_bar" class="container_12">
      <div id="logo" class="grid_3">
        <a title="Go to home page" href="https://git.gnome.org/"><img src="https://static.gnome.org/img/gnome-git.png" alt="GNOME: Git Repository" /></a>
      </div>

      <div id="top_bar" class="grid_9">
        <div class="left">
          <div class="menu-globalnav-container">
            <ul id="menu-globalnav" class="menu">
              <li id="menu-item-1039" class=
              "menu-item menu-item-type-post_type menu-item-object-page menu-item-1039">
              <a href="https://git.gnome.org/">Home</a></li>

              <li id="menu-item-1037" class=
              "menu-item menu-item-type-post_type menu-item-object-page menu-item-1037">
              <a href="https://wiki.gnome.org/Git">Git Help</a></li>
            </ul>
          </div>
        </div>
      </div>
      
    </div>
</div>
<div id='cgit'><table id='header'>
<tr>
<td class='main'><a href='/browse/'>index</a> : <a title='glib' href='/browse/glib/'>glib</a></td><td class='form'><form method='get' action=''>
<select name='h' onchange='this.form.submit();'>
<option value='GLIB_1_1_3_MARTIN'>GLIB_1_1_3_MARTIN</option>
<option value='GLIB_1_1_4_THREADS'>GLIB_1_1_4_THREADS</option>
<option value='GLIB_1_3_HACKS'>GLIB_1_3_HACKS</option>
<option value='GLIB_2_15_0'>GLIB_2_15_0</option>
<option value='dispatch-data'>dispatch-data</option>
<option value='gdbus-daemon'>gdbus-daemon</option>
<option value='gdbus-daemon2'>gdbus-daemon2</option>
<option value='glib-1-2'>glib-1-2</option>
<option value='glib-2-0'>glib-2-0</option>
<option value='glib-2-10'>glib-2-10</option>
<option value='glib-2-12'>glib-2-12</option>
<option value='glib-2-14'>glib-2-14</option>
<option value='glib-2-16'>glib-2-16</option>
<option value='glib-2-18'>glib-2-18</option>
<option value='glib-2-2'>glib-2-2</option>
<option value='glib-2-20'>glib-2-20</option>
<option value='glib-2-22'>glib-2-22</option>
<option value='glib-2-24'>glib-2-24</option>
<option value='glib-2-26'>glib-2-26</option>
<option value='glib-2-28'>glib-2-28</option>
<option value='glib-2-30'>glib-2-30</option>
<option value='glib-2-32'>glib-2-32</option>
<option value='glib-2-34'>glib-2-34</option>
<option value='glib-2-36'>glib-2-36</option>
<option value='glib-2-38'>glib-2-38</option>
<option value='glib-2-4'>glib-2-4</option>
<option value='glib-2-40'>glib-2-40</option>
<option value='glib-2-42'>glib-2-42</option>
<option value='glib-2-44'>glib-2-44</option>
<option value='glib-2-46'>glib-2-46</option>
<option value='glib-2-6'>glib-2-6</option>
<option value='glib-2-8'>glib-2-8</option>
<option value='glib-main-loop'>glib-main-loop</option>
<option value='glib-threads'>glib-threads</option>
<option value='gobject-docs'>gobject-docs</option>
<option value='master' selected='selected'>master</option>
<option value='new-gsettings'>new-gsettings</option>
<option value='signal-performance'>signal-performance</option>
<option value='test/gobjectnew'>test/gobjectnew</option>
<option value='wip/async-io-perf'>wip/async-io-perf</option>
<option value='wip/chergert/garraylist'>wip/chergert/garraylist</option>
<option value='wip/child-catchall'>wip/child-catchall</option>
<option value='wip/coverity-fixes'>wip/coverity-fixes</option>
<option value='wip/csoriano/movestest'>wip/csoriano/movestest</option>
<option value='wip/danw/guri'>wip/danw/guri</option>
<option value='wip/dbusable'>wip/dbusable</option>
<option value='wip/desktop-actions'>wip/desktop-actions</option>
<option value='wip/desrt/gio-tool'>wip/desrt/gio-tool</option>
<option value='wip/doc-fixes'>wip/doc-fixes</option>
<option value='wip/ebassi/application-quit'>wip/ebassi/application-quit</option>
<option value='wip/format-errors'>wip/format-errors</option>
<option value='wip/free'>wip/free</option>
<option value='wip/g-action-print-detailed-name'>wip/g-action-print-detailed-name</option>
<option value='wip/g-dbus-warning'>wip/g-dbus-warning</option>
<option value='wip/gbytes-memfd'>wip/gbytes-memfd</option>
<option value='wip/gbytes-takeover'>wip/gbytes-takeover</option>
<option value='wip/gcleanup'>wip/gcleanup</option>
<option value='wip/gcleanup-desrt'>wip/gcleanup-desrt</option>
<option value='wip/gdesktopappinfo'>wip/gdesktopappinfo</option>
<option value='wip/ghandle'>wip/ghandle</option>
<option value='wip/gheap'>wip/gheap</option>
<option value='wip/gicon'>wip/gicon</option>
<option value='wip/glib-build.mk'>wip/glib-build.mk</option>
<option value='wip/gmaincontext'>wip/gmaincontext</option>
<option value='wip/gmarkupreader'>wip/gmarkupreader</option>
<option value='wip/gnotification'>wip/gnotification</option>
<option value='wip/gobjectnew'>wip/gobjectnew</option>
<option value='wip/gproperty'>wip/gproperty</option>
<option value='wip/gproperty-2'>wip/gproperty-2</option>
<option value='wip/gsettings-list'>wip/gsettings-list</option>
<option value='wip/gsettings-work'>wip/gsettings-work</option>
<option value='wip/gutils-splitup'>wip/gutils-splitup</option>
<option value='wip/gvariant-kdbus'>wip/gvariant-kdbus</option>
<option value='wip/installed-tests'>wip/installed-tests</option>
<option value='wip/kdbus-junk'>wip/kdbus-junk</option>
<option value='wip/listmodel'>wip/listmodel</option>
<option value='wip/locale-monitor'>wip/locale-monitor</option>
<option value='wip/makefile.glib'>wip/makefile.glib</option>
<option value='wip/mapped-bytes'>wip/mapped-bytes</option>
<option value='wip/matthiasc/gio-tool'>wip/matthiasc/gio-tool</option>
<option value='wip/mimeinfo'>wip/mimeinfo</option>
<option value='wip/mount-watcher'>wip/mount-watcher</option>
<option value='wip/new-parser'>wip/new-parser</option>
<option value='wip/pcre-jit'>wip/pcre-jit</option>
<option value='wip/pcre-mark'>wip/pcre-mark</option>
<option value='wip/pcre-update'>wip/pcre-update</option>
<option value='wip/private-rework-3'>wip/private-rework-3</option>
<option value='wip/refptr'>wip/refptr</option>
<option value='wip/resources2'>wip/resources2</option>
<option value='wip/serializable'>wip/serializable</option>
<option value='wip/settings-backend'>wip/settings-backend</option>
<option value='wip/subprocess-2013'>wip/subprocess-2013</option>
<option value='wip/symbol-visibility'>wip/symbol-visibility</option>
<option value='wip/task'>wip/task</option>
<option value='wip/test-cleanup'>wip/test-cleanup</option>
<option value='wip/threadsafe-qdata'>wip/threadsafe-qdata</option>
<option value='wip/unicode-graphemebreak'>wip/unicode-graphemebreak</option>
<option value='wip/version-bounds'>wip/version-bounds</option>
<option value='wip/win32-source-api'>wip/win32-source-api</option>
</select> <input type='submit' name='' value='switch'/></form></td></tr>
<tr><td class='sub'>Low level core library</td><td class='sub right'>C</td></tr></table>
<table class='tabs'><tr><td>
<a href='/browse/glib/'>summary</a><a href='/browse/glib/refs/'>refs</a><a href='/browse/glib/log/gio/tests/gdbus-example-server.c'>log</a><a class='active' href='/browse/glib/tree/gio/tests/gdbus-example-server.c'>tree</a><a href='/browse/glib/commit/gio/tests/gdbus-example-server.c'>commit</a><a href='/browse/glib/diff/gio/tests/gdbus-example-server.c'>diff</a><a href='/browse/glib/stats/gio/tests/gdbus-example-server.c'>stats</a></td><td class='form'><form class='right' method='get' action='/browse/glib/log/gio/tests/gdbus-example-server.c'>
<select name='qt'>
<option value='grep'>log msg</option>
<option value='author'>author</option>
<option value='committer'>committer</option>
<option value='range'>range</option>
</select>
<input class='txt' type='text' size='10' name='q' value=''/>
<input type='submit' value='search'/>
</form>
</td></tr></table>
<div class='path'>path: <a href='/browse/glib/tree/'>root</a>/<a href='/browse/glib/tree/gio'>gio</a>/<a href='/browse/glib/tree/gio/tests'>tests</a>/<a href='/browse/glib/tree/gio/tests/gdbus-example-server.c'>gdbus-example-server.c</a></div><div class='content'>blob: 6f1123d85f5e07dbf96ad5ad234b90a55b34c933 (<a href='/browse/glib/plain/gio/tests/gdbus-example-server.c'>plain</a>)
<table summary='blob content' class='blob'>
<tr><td class='linenumbers'><pre><a id='n1' href='#n1'>1</a>
<a id='n2' href='#n2'>2</a>
<a id='n3' href='#n3'>3</a>
<a id='n4' href='#n4'>4</a>
<a id='n5' href='#n5'>5</a>
<a id='n6' href='#n6'>6</a>
<a id='n7' href='#n7'>7</a>
<a id='n8' href='#n8'>8</a>
<a id='n9' href='#n9'>9</a>
<a id='n10' href='#n10'>10</a>
<a id='n11' href='#n11'>11</a>
<a id='n12' href='#n12'>12</a>
<a id='n13' href='#n13'>13</a>
<a id='n14' href='#n14'>14</a>
<a id='n15' href='#n15'>15</a>
<a id='n16' href='#n16'>16</a>
<a id='n17' href='#n17'>17</a>
<a id='n18' href='#n18'>18</a>
<a id='n19' href='#n19'>19</a>
<a id='n20' href='#n20'>20</a>
<a id='n21' href='#n21'>21</a>
<a id='n22' href='#n22'>22</a>
<a id='n23' href='#n23'>23</a>
<a id='n24' href='#n24'>24</a>
<a id='n25' href='#n25'>25</a>
<a id='n26' href='#n26'>26</a>
<a id='n27' href='#n27'>27</a>
<a id='n28' href='#n28'>28</a>
<a id='n29' href='#n29'>29</a>
<a id='n30' href='#n30'>30</a>
<a id='n31' href='#n31'>31</a>
<a id='n32' href='#n32'>32</a>
<a id='n33' href='#n33'>33</a>
<a id='n34' href='#n34'>34</a>
<a id='n35' href='#n35'>35</a>
<a id='n36' href='#n36'>36</a>
<a id='n37' href='#n37'>37</a>
<a id='n38' href='#n38'>38</a>
<a id='n39' href='#n39'>39</a>
<a id='n40' href='#n40'>40</a>
<a id='n41' href='#n41'>41</a>
<a id='n42' href='#n42'>42</a>
<a id='n43' href='#n43'>43</a>
<a id='n44' href='#n44'>44</a>
<a id='n45' href='#n45'>45</a>
<a id='n46' href='#n46'>46</a>
<a id='n47' href='#n47'>47</a>
<a id='n48' href='#n48'>48</a>
<a id='n49' href='#n49'>49</a>
<a id='n50' href='#n50'>50</a>
<a id='n51' href='#n51'>51</a>
<a id='n52' href='#n52'>52</a>
<a id='n53' href='#n53'>53</a>
<a id='n54' href='#n54'>54</a>
<a id='n55' href='#n55'>55</a>
<a id='n56' href='#n56'>56</a>
<a id='n57' href='#n57'>57</a>
<a id='n58' href='#n58'>58</a>
<a id='n59' href='#n59'>59</a>
<a id='n60' href='#n60'>60</a>
<a id='n61' href='#n61'>61</a>
<a id='n62' href='#n62'>62</a>
<a id='n63' href='#n63'>63</a>
<a id='n64' href='#n64'>64</a>
<a id='n65' href='#n65'>65</a>
<a id='n66' href='#n66'>66</a>
<a id='n67' href='#n67'>67</a>
<a id='n68' href='#n68'>68</a>
<a id='n69' href='#n69'>69</a>
<a id='n70' href='#n70'>70</a>
<a id='n71' href='#n71'>71</a>
<a id='n72' href='#n72'>72</a>
<a id='n73' href='#n73'>73</a>
<a id='n74' href='#n74'>74</a>
<a id='n75' href='#n75'>75</a>
<a id='n76' href='#n76'>76</a>
<a id='n77' href='#n77'>77</a>
<a id='n78' href='#n78'>78</a>
<a id='n79' href='#n79'>79</a>
<a id='n80' href='#n80'>80</a>
<a id='n81' href='#n81'>81</a>
<a id='n82' href='#n82'>82</a>
<a id='n83' href='#n83'>83</a>
<a id='n84' href='#n84'>84</a>
<a id='n85' href='#n85'>85</a>
<a id='n86' href='#n86'>86</a>
<a id='n87' href='#n87'>87</a>
<a id='n88' href='#n88'>88</a>
<a id='n89' href='#n89'>89</a>
<a id='n90' href='#n90'>90</a>
<a id='n91' href='#n91'>91</a>
<a id='n92' href='#n92'>92</a>
<a id='n93' href='#n93'>93</a>
<a id='n94' href='#n94'>94</a>
<a id='n95' href='#n95'>95</a>
<a id='n96' href='#n96'>96</a>
<a id='n97' href='#n97'>97</a>
<a id='n98' href='#n98'>98</a>
<a id='n99' href='#n99'>99</a>
<a id='n100' href='#n100'>100</a>
<a id='n101' href='#n101'>101</a>
<a id='n102' href='#n102'>102</a>
<a id='n103' href='#n103'>103</a>
<a id='n104' href='#n104'>104</a>
<a id='n105' href='#n105'>105</a>
<a id='n106' href='#n106'>106</a>
<a id='n107' href='#n107'>107</a>
<a id='n108' href='#n108'>108</a>
<a id='n109' href='#n109'>109</a>
<a id='n110' href='#n110'>110</a>
<a id='n111' href='#n111'>111</a>
<a id='n112' href='#n112'>112</a>
<a id='n113' href='#n113'>113</a>
<a id='n114' href='#n114'>114</a>
<a id='n115' href='#n115'>115</a>
<a id='n116' href='#n116'>116</a>
<a id='n117' href='#n117'>117</a>
<a id='n118' href='#n118'>118</a>
<a id='n119' href='#n119'>119</a>
<a id='n120' href='#n120'>120</a>
<a id='n121' href='#n121'>121</a>
<a id='n122' href='#n122'>122</a>
<a id='n123' href='#n123'>123</a>
<a id='n124' href='#n124'>124</a>
<a id='n125' href='#n125'>125</a>
<a id='n126' href='#n126'>126</a>
<a id='n127' href='#n127'>127</a>
<a id='n128' href='#n128'>128</a>
<a id='n129' href='#n129'>129</a>
<a id='n130' href='#n130'>130</a>
<a id='n131' href='#n131'>131</a>
<a id='n132' href='#n132'>132</a>
<a id='n133' href='#n133'>133</a>
<a id='n134' href='#n134'>134</a>
<a id='n135' href='#n135'>135</a>
<a id='n136' href='#n136'>136</a>
<a id='n137' href='#n137'>137</a>
<a id='n138' href='#n138'>138</a>
<a id='n139' href='#n139'>139</a>
<a id='n140' href='#n140'>140</a>
<a id='n141' href='#n141'>141</a>
<a id='n142' href='#n142'>142</a>
<a id='n143' href='#n143'>143</a>
<a id='n144' href='#n144'>144</a>
<a id='n145' href='#n145'>145</a>
<a id='n146' href='#n146'>146</a>
<a id='n147' href='#n147'>147</a>
<a id='n148' href='#n148'>148</a>
<a id='n149' href='#n149'>149</a>
<a id='n150' href='#n150'>150</a>
<a id='n151' href='#n151'>151</a>
<a id='n152' href='#n152'>152</a>
<a id='n153' href='#n153'>153</a>
<a id='n154' href='#n154'>154</a>
<a id='n155' href='#n155'>155</a>
<a id='n156' href='#n156'>156</a>
<a id='n157' href='#n157'>157</a>
<a id='n158' href='#n158'>158</a>
<a id='n159' href='#n159'>159</a>
<a id='n160' href='#n160'>160</a>
<a id='n161' href='#n161'>161</a>
<a id='n162' href='#n162'>162</a>
<a id='n163' href='#n163'>163</a>
<a id='n164' href='#n164'>164</a>
<a id='n165' href='#n165'>165</a>
<a id='n166' href='#n166'>166</a>
<a id='n167' href='#n167'>167</a>
<a id='n168' href='#n168'>168</a>
<a id='n169' href='#n169'>169</a>
<a id='n170' href='#n170'>170</a>
<a id='n171' href='#n171'>171</a>
<a id='n172' href='#n172'>172</a>
<a id='n173' href='#n173'>173</a>
<a id='n174' href='#n174'>174</a>
<a id='n175' href='#n175'>175</a>
<a id='n176' href='#n176'>176</a>
<a id='n177' href='#n177'>177</a>
<a id='n178' href='#n178'>178</a>
<a id='n179' href='#n179'>179</a>
<a id='n180' href='#n180'>180</a>
<a id='n181' href='#n181'>181</a>
<a id='n182' href='#n182'>182</a>
<a id='n183' href='#n183'>183</a>
<a id='n184' href='#n184'>184</a>
<a id='n185' href='#n185'>185</a>
<a id='n186' href='#n186'>186</a>
<a id='n187' href='#n187'>187</a>
<a id='n188' href='#n188'>188</a>
<a id='n189' href='#n189'>189</a>
<a id='n190' href='#n190'>190</a>
<a id='n191' href='#n191'>191</a>
<a id='n192' href='#n192'>192</a>
<a id='n193' href='#n193'>193</a>
<a id='n194' href='#n194'>194</a>
<a id='n195' href='#n195'>195</a>
<a id='n196' href='#n196'>196</a>
<a id='n197' href='#n197'>197</a>
<a id='n198' href='#n198'>198</a>
<a id='n199' href='#n199'>199</a>
<a id='n200' href='#n200'>200</a>
<a id='n201' href='#n201'>201</a>
<a id='n202' href='#n202'>202</a>
<a id='n203' href='#n203'>203</a>
<a id='n204' href='#n204'>204</a>
<a id='n205' href='#n205'>205</a>
<a id='n206' href='#n206'>206</a>
<a id='n207' href='#n207'>207</a>
<a id='n208' href='#n208'>208</a>
<a id='n209' href='#n209'>209</a>
<a id='n210' href='#n210'>210</a>
<a id='n211' href='#n211'>211</a>
<a id='n212' href='#n212'>212</a>
<a id='n213' href='#n213'>213</a>
<a id='n214' href='#n214'>214</a>
<a id='n215' href='#n215'>215</a>
<a id='n216' href='#n216'>216</a>
<a id='n217' href='#n217'>217</a>
<a id='n218' href='#n218'>218</a>
<a id='n219' href='#n219'>219</a>
<a id='n220' href='#n220'>220</a>
<a id='n221' href='#n221'>221</a>
<a id='n222' href='#n222'>222</a>
<a id='n223' href='#n223'>223</a>
<a id='n224' href='#n224'>224</a>
<a id='n225' href='#n225'>225</a>
<a id='n226' href='#n226'>226</a>
<a id='n227' href='#n227'>227</a>
<a id='n228' href='#n228'>228</a>
<a id='n229' href='#n229'>229</a>
<a id='n230' href='#n230'>230</a>
<a id='n231' href='#n231'>231</a>
<a id='n232' href='#n232'>232</a>
<a id='n233' href='#n233'>233</a>
<a id='n234' href='#n234'>234</a>
<a id='n235' href='#n235'>235</a>
<a id='n236' href='#n236'>236</a>
<a id='n237' href='#n237'>237</a>
<a id='n238' href='#n238'>238</a>
<a id='n239' href='#n239'>239</a>
<a id='n240' href='#n240'>240</a>
<a id='n241' href='#n241'>241</a>
<a id='n242' href='#n242'>242</a>
<a id='n243' href='#n243'>243</a>
<a id='n244' href='#n244'>244</a>
<a id='n245' href='#n245'>245</a>
<a id='n246' href='#n246'>246</a>
<a id='n247' href='#n247'>247</a>
<a id='n248' href='#n248'>248</a>
<a id='n249' href='#n249'>249</a>
<a id='n250' href='#n250'>250</a>
<a id='n251' href='#n251'>251</a>
<a id='n252' href='#n252'>252</a>
<a id='n253' href='#n253'>253</a>
<a id='n254' href='#n254'>254</a>
<a id='n255' href='#n255'>255</a>
<a id='n256' href='#n256'>256</a>
<a id='n257' href='#n257'>257</a>
<a id='n258' href='#n258'>258</a>
<a id='n259' href='#n259'>259</a>
<a id='n260' href='#n260'>260</a>
<a id='n261' href='#n261'>261</a>
<a id='n262' href='#n262'>262</a>
<a id='n263' href='#n263'>263</a>
<a id='n264' href='#n264'>264</a>
<a id='n265' href='#n265'>265</a>
<a id='n266' href='#n266'>266</a>
<a id='n267' href='#n267'>267</a>
<a id='n268' href='#n268'>268</a>
<a id='n269' href='#n269'>269</a>
<a id='n270' href='#n270'>270</a>
<a id='n271' href='#n271'>271</a>
<a id='n272' href='#n272'>272</a>
<a id='n273' href='#n273'>273</a>
<a id='n274' href='#n274'>274</a>
<a id='n275' href='#n275'>275</a>
<a id='n276' href='#n276'>276</a>
<a id='n277' href='#n277'>277</a>
<a id='n278' href='#n278'>278</a>
<a id='n279' href='#n279'>279</a>
<a id='n280' href='#n280'>280</a>
<a id='n281' href='#n281'>281</a>
<a id='n282' href='#n282'>282</a>
<a id='n283' href='#n283'>283</a>
<a id='n284' href='#n284'>284</a>
<a id='n285' href='#n285'>285</a>
<a id='n286' href='#n286'>286</a>
<a id='n287' href='#n287'>287</a>
<a id='n288' href='#n288'>288</a>
<a id='n289' href='#n289'>289</a>
<a id='n290' href='#n290'>290</a>
<a id='n291' href='#n291'>291</a>
<a id='n292' href='#n292'>292</a>
<a id='n293' href='#n293'>293</a>
<a id='n294' href='#n294'>294</a>
<a id='n295' href='#n295'>295</a>
<a id='n296' href='#n296'>296</a>
<a id='n297' href='#n297'>297</a>
<a id='n298' href='#n298'>298</a>
<a id='n299' href='#n299'>299</a>
<a id='n300' href='#n300'>300</a>
<a id='n301' href='#n301'>301</a>
<a id='n302' href='#n302'>302</a>
<a id='n303' href='#n303'>303</a>
<a id='n304' href='#n304'>304</a>
<a id='n305' href='#n305'>305</a>
<a id='n306' href='#n306'>306</a>
<a id='n307' href='#n307'>307</a>
<a id='n308' href='#n308'>308</a>
<a id='n309' href='#n309'>309</a>
<a id='n310' href='#n310'>310</a>
<a id='n311' href='#n311'>311</a>
<a id='n312' href='#n312'>312</a>
<a id='n313' href='#n313'>313</a>
<a id='n314' href='#n314'>314</a>
<a id='n315' href='#n315'>315</a>
<a id='n316' href='#n316'>316</a>
<a id='n317' href='#n317'>317</a>
<a id='n318' href='#n318'>318</a>
<a id='n319' href='#n319'>319</a>
<a id='n320' href='#n320'>320</a>
<a id='n321' href='#n321'>321</a>
<a id='n322' href='#n322'>322</a>
<a id='n323' href='#n323'>323</a>
<a id='n324' href='#n324'>324</a>
<a id='n325' href='#n325'>325</a>
<a id='n326' href='#n326'>326</a>
<a id='n327' href='#n327'>327</a>
<a id='n328' href='#n328'>328</a>
<a id='n329' href='#n329'>329</a>
<a id='n330' href='#n330'>330</a>
<a id='n331' href='#n331'>331</a>
<a id='n332' href='#n332'>332</a>
<a id='n333' href='#n333'>333</a>
<a id='n334' href='#n334'>334</a>
<a id='n335' href='#n335'>335</a>
<a id='n336' href='#n336'>336</a>
<a id='n337' href='#n337'>337</a>
<a id='n338' href='#n338'>338</a>
<a id='n339' href='#n339'>339</a>
<a id='n340' href='#n340'>340</a>
<a id='n341' href='#n341'>341</a>
<a id='n342' href='#n342'>342</a>
<a id='n343' href='#n343'>343</a>
<a id='n344' href='#n344'>344</a>
<a id='n345' href='#n345'>345</a>
<a id='n346' href='#n346'>346</a>
<a id='n347' href='#n347'>347</a>
<a id='n348' href='#n348'>348</a>
<a id='n349' href='#n349'>349</a>
<a id='n350' href='#n350'>350</a>
<a id='n351' href='#n351'>351</a>
<a id='n352' href='#n352'>352</a>
<a id='n353' href='#n353'>353</a>
<a id='n354' href='#n354'>354</a>
<a id='n355' href='#n355'>355</a>
<a id='n356' href='#n356'>356</a>
<a id='n357' href='#n357'>357</a>
<a id='n358' href='#n358'>358</a>
<a id='n359' href='#n359'>359</a>
<a id='n360' href='#n360'>360</a>
<a id='n361' href='#n361'>361</a>
<a id='n362' href='#n362'>362</a>
<a id='n363' href='#n363'>363</a>
<a id='n364' href='#n364'>364</a>
<a id='n365' href='#n365'>365</a>
<a id='n366' href='#n366'>366</a>
<a id='n367' href='#n367'>367</a>
<a id='n368' href='#n368'>368</a>
<a id='n369' href='#n369'>369</a>
<a id='n370' href='#n370'>370</a>
<a id='n371' href='#n371'>371</a>
<a id='n372' href='#n372'>372</a>
<a id='n373' href='#n373'>373</a>
<a id='n374' href='#n374'>374</a>
<a id='n375' href='#n375'>375</a>
<a id='n376' href='#n376'>376</a>
<a id='n377' href='#n377'>377</a>
<a id='n378' href='#n378'>378</a>
<a id='n379' href='#n379'>379</a>
<a id='n380' href='#n380'>380</a>
<a id='n381' href='#n381'>381</a>
<a id='n382' href='#n382'>382</a>
<a id='n383' href='#n383'>383</a>
<a id='n384' href='#n384'>384</a>
<a id='n385' href='#n385'>385</a>
<a id='n386' href='#n386'>386</a>
<a id='n387' href='#n387'>387</a>
<a id='n388' href='#n388'>388</a>
<a id='n389' href='#n389'>389</a>
<a id='n390' href='#n390'>390</a>
</pre></td>
<td class='lines'><pre><code><span class="hl ppc">#include &lt;gio/gio.h&gt;</span>
<span class="hl ppc">#include &lt;stdlib.h&gt;</span>

<span class="hl ppc">#ifdef G_OS_UNIX</span>
<span class="hl ppc">#include &lt;gio/gunixfdlist.h&gt;</span>
<span class="hl com">/* For STDOUT_FILENO */</span>
<span class="hl ppc">#include &lt;unistd.h&gt;</span>
<span class="hl ppc">#endif</span>

<span class="hl com">/* ---------------------------------------------------------------------------------------------------- */</span>

<span class="hl kwb">static</span> GDBusNodeInfo <span class="hl opt">*</span>introspection_data <span class="hl opt">=</span> NULL<span class="hl opt">;</span>

<span class="hl com">/* Introspection data for the service we are exporting */</span>
<span class="hl kwb">static const</span> gchar introspection_xml<span class="hl opt">[] =</span>
  <span class="hl str">&quot;&lt;node&gt;&quot;</span>
  <span class="hl str">&quot;  &lt;interface name='org.gtk.GDBus.TestInterface'&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;annotation name='org.gtk.GDBus.Annotation' value='OnInterface'/&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;annotation name='org.gtk.GDBus.Annotation' value='AlsoOnInterface'/&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;method name='HelloWorld'&gt;&quot;</span>
  <span class="hl str">&quot;      &lt;annotation name='org.gtk.GDBus.Annotation' value='OnMethod'/&gt;&quot;</span>
  <span class="hl str">&quot;      &lt;arg type='s' name='greeting' direction='in'/&gt;&quot;</span>
  <span class="hl str">&quot;      &lt;arg type='s' name='response' direction='out'/&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;/method&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;method name='EmitSignal'&gt;&quot;</span>
  <span class="hl str">&quot;      &lt;arg type='d' name='speed_in_mph' direction='in'&gt;&quot;</span>
  <span class="hl str">&quot;        &lt;annotation name='org.gtk.GDBus.Annotation' value='OnArg'/&gt;&quot;</span>
  <span class="hl str">&quot;      &lt;/arg&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;/method&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;method name='GimmeStdout'/&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;signal name='VelocityChanged'&gt;&quot;</span>
  <span class="hl str">&quot;      &lt;annotation name='org.gtk.GDBus.Annotation' value='Onsignal'/&gt;&quot;</span>
  <span class="hl str">&quot;      &lt;arg type='d' name='speed_in_mph'/&gt;&quot;</span>
  <span class="hl str">&quot;      &lt;arg type='s' name='speed_as_string'&gt;&quot;</span>
  <span class="hl str">&quot;        &lt;annotation name='org.gtk.GDBus.Annotation' value='OnArg_NonFirst'/&gt;&quot;</span>
  <span class="hl str">&quot;      &lt;/arg&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;/signal&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;property type='s' name='FluxCapicitorName' access='read'&gt;&quot;</span>
  <span class="hl str">&quot;      &lt;annotation name='org.gtk.GDBus.Annotation' value='OnProperty'&gt;&quot;</span>
  <span class="hl str">&quot;        &lt;annotation name='org.gtk.GDBus.Annotation' value='OnAnnotation_YesThisIsCrazy'/&gt;&quot;</span>
  <span class="hl str">&quot;      &lt;/annotation&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;/property&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;property type='s' name='Title' access='readwrite'/&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;property type='s' name='ReadingAlwaysThrowsError' access='read'/&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;property type='s' name='WritingAlwaysThrowsError' access='readwrite'/&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;property type='s' name='OnlyWritable' access='write'/&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;property type='s' name='Foo' access='read'/&gt;&quot;</span>
  <span class="hl str">&quot;    &lt;property type='s' name='Bar' access='read'/&gt;&quot;</span>
  <span class="hl str">&quot;  &lt;/interface&gt;&quot;</span>
  <span class="hl str">&quot;&lt;/node&gt;&quot;</span><span class="hl opt">;</span>

<span class="hl com">/* ---------------------------------------------------------------------------------------------------- */</span>

<span class="hl kwb">static void</span>
<span class="hl kwd">handle_method_call</span> <span class="hl opt">(</span>GDBusConnection       <span class="hl opt">*</span>connection<span class="hl opt">,</span>
                    <span class="hl kwb">const</span> gchar           <span class="hl opt">*</span>sender<span class="hl opt">,</span>
                    <span class="hl kwb">const</span> gchar           <span class="hl opt">*</span>object_path<span class="hl opt">,</span>
                    <span class="hl kwb">const</span> gchar           <span class="hl opt">*</span>interface_name<span class="hl opt">,</span>
                    <span class="hl kwb">const</span> gchar           <span class="hl opt">*</span>method_name<span class="hl opt">,</span>
                    GVariant              <span class="hl opt">*</span>parameters<span class="hl opt">,</span>
                    GDBusMethodInvocation <span class="hl opt">*</span>invocation<span class="hl opt">,</span>
                    gpointer               user_data<span class="hl opt">)</span>
<span class="hl opt">{</span>
  <span class="hl kwa">if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>method_name<span class="hl opt">,</span> <span class="hl str">&quot;HelloWorld&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
    <span class="hl opt">{</span>
      <span class="hl kwb">const</span> gchar <span class="hl opt">*</span>greeting<span class="hl opt">;</span>

      <span class="hl kwd">g_variant_get</span> <span class="hl opt">(</span>parameters<span class="hl opt">,</span> <span class="hl str">&quot;(&amp;s)&quot;</span><span class="hl opt">, &amp;</span>greeting<span class="hl opt">);</span>

      <span class="hl kwa">if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>greeting<span class="hl opt">,</span> <span class="hl str">&quot;Return Unregistered&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
        <span class="hl opt">{</span>
          <span class="hl kwd">g_dbus_method_invocation_return_error</span> <span class="hl opt">(</span>invocation<span class="hl opt">,</span>
                                                 G_IO_ERROR<span class="hl opt">,</span>
                                                 G_IO_ERROR_FAILED_HANDLED<span class="hl opt">,</span>
                                                 <span class="hl str">&quot;As requested, here's a GError not registered (G_IO_ERROR_FAILED_HANDLED)&quot;</span><span class="hl opt">);</span>
        <span class="hl opt">}</span>
      <span class="hl kwa">else if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>greeting<span class="hl opt">,</span> <span class="hl str">&quot;Return Registered&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
        <span class="hl opt">{</span>
          <span class="hl kwd">g_dbus_method_invocation_return_error</span> <span class="hl opt">(</span>invocation<span class="hl opt">,</span>
                                                 G_DBUS_ERROR<span class="hl opt">,</span>
                                                 G_DBUS_ERROR_MATCH_RULE_NOT_FOUND<span class="hl opt">,</span>
                                                 <span class="hl str">&quot;As requested, here's a GError that is registered (G_DBUS_ERROR_MATCH_RULE_NOT_FOUND)&quot;</span><span class="hl opt">);</span>
        <span class="hl opt">}</span>
      <span class="hl kwa">else if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>greeting<span class="hl opt">,</span> <span class="hl str">&quot;Return Raw&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
        <span class="hl opt">{</span>
          <span class="hl kwd">g_dbus_method_invocation_return_dbus_error</span> <span class="hl opt">(</span>invocation<span class="hl opt">,</span>
                                                      <span class="hl str">&quot;org.gtk.GDBus.SomeErrorName&quot;</span><span class="hl opt">,</span>
                                                      <span class="hl str">&quot;As requested, here's a raw D-Bus error&quot;</span><span class="hl opt">);</span>
        <span class="hl opt">}</span>
      <span class="hl kwa">else</span>
        <span class="hl opt">{</span>
          gchar <span class="hl opt">*</span>response<span class="hl opt">;</span>
          response <span class="hl opt">=</span> <span class="hl kwd">g_strdup_printf</span> <span class="hl opt">(</span><span class="hl str">&quot;You greeted me with '%s'. Thanks!&quot;</span><span class="hl opt">,</span> greeting<span class="hl opt">);</span>
          <span class="hl kwd">g_dbus_method_invocation_return_value</span> <span class="hl opt">(</span>invocation<span class="hl opt">,</span>
                                                 <span class="hl kwd">g_variant_new</span> <span class="hl opt">(</span><span class="hl str">&quot;(s)&quot;</span><span class="hl opt">,</span> response<span class="hl opt">));</span>
          <span class="hl kwd">g_free</span> <span class="hl opt">(</span>response<span class="hl opt">);</span>
        <span class="hl opt">}</span>
    <span class="hl opt">}</span>
  <span class="hl kwa">else if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>method_name<span class="hl opt">,</span> <span class="hl str">&quot;EmitSignal&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
    <span class="hl opt">{</span>
      GError <span class="hl opt">*</span>local_error<span class="hl opt">;</span>
      gdouble speed_in_mph<span class="hl opt">;</span>
      gchar <span class="hl opt">*</span>speed_as_string<span class="hl opt">;</span>

      <span class="hl kwd">g_variant_get</span> <span class="hl opt">(</span>parameters<span class="hl opt">,</span> <span class="hl str">&quot;(d)&quot;</span><span class="hl opt">, &amp;</span>speed_in_mph<span class="hl opt">);</span>
      speed_as_string <span class="hl opt">=</span> <span class="hl kwd">g_strdup_printf</span> <span class="hl opt">(</span><span class="hl str">&quot;%g mph!&quot;</span><span class="hl opt">,</span> speed_in_mph<span class="hl opt">);</span>

      local_error <span class="hl opt">=</span> NULL<span class="hl opt">;</span>
      <span class="hl kwd">g_dbus_connection_emit_signal</span> <span class="hl opt">(</span>connection<span class="hl opt">,</span>
                                     NULL<span class="hl opt">,</span>
                                     object_path<span class="hl opt">,</span>
                                     interface_name<span class="hl opt">,</span>
                                     <span class="hl str">&quot;VelocityChanged&quot;</span><span class="hl opt">,</span>
                                     <span class="hl kwd">g_variant_new</span> <span class="hl opt">(</span><span class="hl str">&quot;(ds)&quot;</span><span class="hl opt">,</span>
                                                    speed_in_mph<span class="hl opt">,</span>
                                                    speed_as_string<span class="hl opt">),</span>
                                     <span class="hl opt">&amp;</span>local_error<span class="hl opt">);</span>
      <span class="hl kwd">g_assert_no_error</span> <span class="hl opt">(</span>local_error<span class="hl opt">);</span>
      <span class="hl kwd">g_free</span> <span class="hl opt">(</span>speed_as_string<span class="hl opt">);</span>

      <span class="hl kwd">g_dbus_method_invocation_return_value</span> <span class="hl opt">(</span>invocation<span class="hl opt">,</span> NULL<span class="hl opt">);</span>
    <span class="hl opt">}</span>
  <span class="hl kwa">else if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>method_name<span class="hl opt">,</span> <span class="hl str">&quot;GimmeStdout&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
    <span class="hl opt">{</span>
<span class="hl ppc">#ifdef G_OS_UNIX</span>
      <span class="hl kwa">if</span> <span class="hl opt">(</span><span class="hl kwd">g_dbus_connection_get_capabilities</span> <span class="hl opt">(</span>connection<span class="hl opt">) &amp;</span> G_DBUS_CAPABILITY_FLAGS_UNIX_FD_PASSING<span class="hl opt">)</span>
        <span class="hl opt">{</span>
          GDBusMessage <span class="hl opt">*</span>reply<span class="hl opt">;</span>
          GUnixFDList <span class="hl opt">*</span>fd_list<span class="hl opt">;</span>
          GError <span class="hl opt">*</span>error<span class="hl opt">;</span>

          fd_list <span class="hl opt">=</span> <span class="hl kwd">g_unix_fd_list_new</span> <span class="hl opt">();</span>
          error <span class="hl opt">=</span> NULL<span class="hl opt">;</span>
          <span class="hl kwd">g_unix_fd_list_append</span> <span class="hl opt">(</span>fd_list<span class="hl opt">,</span> STDOUT_FILENO<span class="hl opt">, &amp;</span>error<span class="hl opt">);</span>
          <span class="hl kwd">g_assert_no_error</span> <span class="hl opt">(</span>error<span class="hl opt">);</span>

          reply <span class="hl opt">=</span> <span class="hl kwd">g_dbus_message_new_method_reply</span> <span class="hl opt">(</span><span class="hl kwd">g_dbus_method_invocation_get_message</span> <span class="hl opt">(</span>invocation<span class="hl opt">));</span>
          <span class="hl kwd">g_dbus_message_set_unix_fd_list</span> <span class="hl opt">(</span>reply<span class="hl opt">,</span> fd_list<span class="hl opt">);</span>

          error <span class="hl opt">=</span> NULL<span class="hl opt">;</span>
          <span class="hl kwd">g_dbus_connection_send_message</span> <span class="hl opt">(</span>connection<span class="hl opt">,</span>
                                          reply<span class="hl opt">,</span>
                                          G_DBUS_SEND_MESSAGE_FLAGS_NONE<span class="hl opt">,</span>
                                          NULL<span class="hl opt">,</span> <span class="hl com">/* out_serial */</span>
                                          <span class="hl opt">&amp;</span>error<span class="hl opt">);</span>
          <span class="hl kwd">g_assert_no_error</span> <span class="hl opt">(</span>error<span class="hl opt">);</span>

          <span class="hl kwd">g_object_unref</span> <span class="hl opt">(</span>invocation<span class="hl opt">);</span>
          <span class="hl kwd">g_object_unref</span> <span class="hl opt">(</span>fd_list<span class="hl opt">);</span>
          <span class="hl kwd">g_object_unref</span> <span class="hl opt">(</span>reply<span class="hl opt">);</span>
        <span class="hl opt">}</span>
      <span class="hl kwa">else</span>
        <span class="hl opt">{</span>
          <span class="hl kwd">g_dbus_method_invocation_return_dbus_error</span> <span class="hl opt">(</span>invocation<span class="hl opt">,</span>
                                                      <span class="hl str">&quot;org.gtk.GDBus.Failed&quot;</span><span class="hl opt">,</span>
                                                      <span class="hl str">&quot;Your message bus daemon does not support file descriptor passing (need D-Bus &gt;= 1.3.0)&quot;</span><span class="hl opt">);</span>
        <span class="hl opt">}</span>
<span class="hl ppc">#else</span>
      <span class="hl kwd">g_dbus_method_invocation_return_dbus_error</span> <span class="hl opt">(</span>invocation<span class="hl opt">,</span>
                                                  <span class="hl str">&quot;org.gtk.GDBus.NotOnUnix&quot;</span><span class="hl opt">,</span>
                                                  <span class="hl str">&quot;Your OS does not support file descriptor passing&quot;</span><span class="hl opt">);</span>
<span class="hl ppc">#endif</span>
    <span class="hl opt">}</span>
<span class="hl opt">}</span>

<span class="hl kwb">static</span> gchar <span class="hl opt">*</span>_global_title <span class="hl opt">=</span> NULL<span class="hl opt">;</span>

<span class="hl kwb">static</span> gboolean swap_a_and_b <span class="hl opt">=</span> FALSE<span class="hl opt">;</span>

<span class="hl kwb">static</span> GVariant <span class="hl opt">*</span>
<span class="hl kwd">handle_get_property</span> <span class="hl opt">(</span>GDBusConnection  <span class="hl opt">*</span>connection<span class="hl opt">,</span>
                     <span class="hl kwb">const</span> gchar      <span class="hl opt">*</span>sender<span class="hl opt">,</span>
                     <span class="hl kwb">const</span> gchar      <span class="hl opt">*</span>object_path<span class="hl opt">,</span>
                     <span class="hl kwb">const</span> gchar      <span class="hl opt">*</span>interface_name<span class="hl opt">,</span>
                     <span class="hl kwb">const</span> gchar      <span class="hl opt">*</span>property_name<span class="hl opt">,</span>
                     GError          <span class="hl opt">**</span>error<span class="hl opt">,</span>
                     gpointer          user_data<span class="hl opt">)</span>
<span class="hl opt">{</span>
  GVariant <span class="hl opt">*</span>ret<span class="hl opt">;</span>

  ret <span class="hl opt">=</span> NULL<span class="hl opt">;</span>
  <span class="hl kwa">if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>property_name<span class="hl opt">,</span> <span class="hl str">&quot;FluxCapicitorName&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
    <span class="hl opt">{</span>
      ret <span class="hl opt">=</span> <span class="hl kwd">g_variant_new_string</span> <span class="hl opt">(</span><span class="hl str">&quot;DeLorean&quot;</span><span class="hl opt">);</span>
    <span class="hl opt">}</span>
  <span class="hl kwa">else if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>property_name<span class="hl opt">,</span> <span class="hl str">&quot;Title&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
    <span class="hl opt">{</span>
      <span class="hl kwa">if</span> <span class="hl opt">(</span>_global_title <span class="hl opt">==</span> NULL<span class="hl opt">)</span>
        _global_title <span class="hl opt">=</span> <span class="hl kwd">g_strdup</span> <span class="hl opt">(</span><span class="hl str">&quot;Back To C!&quot;</span><span class="hl opt">);</span>
      ret <span class="hl opt">=</span> <span class="hl kwd">g_variant_new_string</span> <span class="hl opt">(</span>_global_title<span class="hl opt">);</span>
    <span class="hl opt">}</span>
  <span class="hl kwa">else if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>property_name<span class="hl opt">,</span> <span class="hl str">&quot;ReadingAlwaysThrowsError&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
    <span class="hl opt">{</span>
      <span class="hl kwd">g_set_error</span> <span class="hl opt">(</span>error<span class="hl opt">,</span>
                   G_IO_ERROR<span class="hl opt">,</span>
                   G_IO_ERROR_FAILED<span class="hl opt">,</span>
                   <span class="hl str">&quot;Hello %s. I thought I said reading this property &quot;</span>
                   <span class="hl str">&quot;always results in an error. kthxbye&quot;</span><span class="hl opt">,</span>
                   sender<span class="hl opt">);</span>
    <span class="hl opt">}</span>
  <span class="hl kwa">else if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>property_name<span class="hl opt">,</span> <span class="hl str">&quot;WritingAlwaysThrowsError&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
    <span class="hl opt">{</span>
      ret <span class="hl opt">=</span> <span class="hl kwd">g_variant_new_string</span> <span class="hl opt">(</span><span class="hl str">&quot;There's no home like home&quot;</span><span class="hl opt">);</span>
    <span class="hl opt">}</span>
  <span class="hl kwa">else if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>property_name<span class="hl opt">,</span> <span class="hl str">&quot;Foo&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
    <span class="hl opt">{</span>
      ret <span class="hl opt">=</span> <span class="hl kwd">g_variant_new_string</span> <span class="hl opt">(</span>swap_a_and_b ? <span class="hl str">&quot;Tock&quot;</span> <span class="hl opt">:</span> <span class="hl str">&quot;Tick&quot;</span><span class="hl opt">);</span>
    <span class="hl opt">}</span>
  <span class="hl kwa">else if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>property_name<span class="hl opt">,</span> <span class="hl str">&quot;Bar&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
    <span class="hl opt">{</span>
      ret <span class="hl opt">=</span> <span class="hl kwd">g_variant_new_string</span> <span class="hl opt">(</span>swap_a_and_b ? <span class="hl str">&quot;Tick&quot;</span> <span class="hl opt">:</span> <span class="hl str">&quot;Tock&quot;</span><span class="hl opt">);</span>
    <span class="hl opt">}</span>

  <span class="hl kwa">return</span> ret<span class="hl opt">;</span>
<span class="hl opt">}</span>

<span class="hl kwb">static</span> gboolean
<span class="hl kwd">handle_set_property</span> <span class="hl opt">(</span>GDBusConnection  <span class="hl opt">*</span>connection<span class="hl opt">,</span>
                     <span class="hl kwb">const</span> gchar      <span class="hl opt">*</span>sender<span class="hl opt">,</span>
                     <span class="hl kwb">const</span> gchar      <span class="hl opt">*</span>object_path<span class="hl opt">,</span>
                     <span class="hl kwb">const</span> gchar      <span class="hl opt">*</span>interface_name<span class="hl opt">,</span>
                     <span class="hl kwb">const</span> gchar      <span class="hl opt">*</span>property_name<span class="hl opt">,</span>
                     GVariant         <span class="hl opt">*</span>value<span class="hl opt">,</span>
                     GError          <span class="hl opt">**</span>error<span class="hl opt">,</span>
                     gpointer          user_data<span class="hl opt">)</span>
<span class="hl opt">{</span>
  <span class="hl kwa">if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>property_name<span class="hl opt">,</span> <span class="hl str">&quot;Title&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
    <span class="hl opt">{</span>
      <span class="hl kwa">if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>_global_title<span class="hl opt">,</span> <span class="hl kwd">g_variant_get_string</span> <span class="hl opt">(</span>value<span class="hl opt">,</span> NULL<span class="hl opt">)) !=</span> <span class="hl num">0</span><span class="hl opt">)</span>
        <span class="hl opt">{</span>
          GVariantBuilder <span class="hl opt">*</span>builder<span class="hl opt">;</span>
          GError <span class="hl opt">*</span>local_error<span class="hl opt">;</span>

          <span class="hl kwd">g_free</span> <span class="hl opt">(</span>_global_title<span class="hl opt">);</span>
          _global_title <span class="hl opt">=</span> <span class="hl kwd">g_variant_dup_string</span> <span class="hl opt">(</span>value<span class="hl opt">,</span> NULL<span class="hl opt">);</span>

          local_error <span class="hl opt">=</span> NULL<span class="hl opt">;</span>
          builder <span class="hl opt">=</span> <span class="hl kwd">g_variant_builder_new</span> <span class="hl opt">(</span>G_VARIANT_TYPE_ARRAY<span class="hl opt">);</span>
          <span class="hl kwd">g_variant_builder_add</span> <span class="hl opt">(</span>builder<span class="hl opt">,</span>
                                 <span class="hl str">&quot;{sv}&quot;</span><span class="hl opt">,</span>
                                 <span class="hl str">&quot;Title&quot;</span><span class="hl opt">,</span>
                                 <span class="hl kwd">g_variant_new_string</span> <span class="hl opt">(</span>_global_title<span class="hl opt">));</span>
          <span class="hl kwd">g_dbus_connection_emit_signal</span> <span class="hl opt">(</span>connection<span class="hl opt">,</span>
                                         NULL<span class="hl opt">,</span>
                                         object_path<span class="hl opt">,</span>
                                         <span class="hl str">&quot;org.freedesktop.DBus.Properties&quot;</span><span class="hl opt">,</span>
                                         <span class="hl str">&quot;PropertiesChanged&quot;</span><span class="hl opt">,</span>
                                         <span class="hl kwd">g_variant_new</span> <span class="hl opt">(</span><span class="hl str">&quot;(sa{sv}as)&quot;</span><span class="hl opt">,</span>
                                                        interface_name<span class="hl opt">,</span>
                                                        builder<span class="hl opt">,</span>
                                                        NULL<span class="hl opt">),</span>
                                         <span class="hl opt">&amp;</span>local_error<span class="hl opt">);</span>
          <span class="hl kwd">g_assert_no_error</span> <span class="hl opt">(</span>local_error<span class="hl opt">);</span>
        <span class="hl opt">}</span>
    <span class="hl opt">}</span>
  <span class="hl kwa">else if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>property_name<span class="hl opt">,</span> <span class="hl str">&quot;ReadingAlwaysThrowsError&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
    <span class="hl opt">{</span>
      <span class="hl com">/* do nothing - they can't read it after all! */</span>
    <span class="hl opt">}</span>
  <span class="hl kwa">else if</span> <span class="hl opt">(</span><span class="hl kwd">g_strcmp0</span> <span class="hl opt">(</span>property_name<span class="hl opt">,</span> <span class="hl str">&quot;WritingAlwaysThrowsError&quot;</span><span class="hl opt">) ==</span> <span class="hl num">0</span><span class="hl opt">)</span>
    <span class="hl opt">{</span>
      <span class="hl kwd">g_set_error</span> <span class="hl opt">(</span>error<span class="hl opt">,</span>
                   G_IO_ERROR<span class="hl opt">,</span>
                   G_IO_ERROR_FAILED<span class="hl opt">,</span>
                   <span class="hl str">&quot;Hello AGAIN %s. I thought I said writing this property &quot;</span>
                   <span class="hl str">&quot;always results in an error. kthxbye&quot;</span><span class="hl opt">,</span>
                   sender<span class="hl opt">);</span>
    <span class="hl opt">}</span>

  <span class="hl kwa">return</span> <span class="hl opt">*</span>error <span class="hl opt">==</span> NULL<span class="hl opt">;</span>
<span class="hl opt">}</span>


<span class="hl com">/* for now */</span>
<span class="hl kwb">static const</span> GDBusInterfaceVTable interface_vtable <span class="hl opt">=</span>
<span class="hl opt">{</span>
  handle_method_call<span class="hl opt">,</span>
  handle_get_property<span class="hl opt">,</span>
  handle_set_property
<span class="hl opt">};</span>

<span class="hl com">/* ---------------------------------------------------------------------------------------------------- */</span>

<span class="hl kwb">static</span> gboolean
<span class="hl kwd">on_timeout_cb</span> <span class="hl opt">(</span>gpointer user_data<span class="hl opt">)</span>
<span class="hl opt">{</span>
  GDBusConnection <span class="hl opt">*</span>connection <span class="hl opt">=</span> <span class="hl kwd">G_DBUS_CONNECTION</span> <span class="hl opt">(</span>user_data<span class="hl opt">);</span>
  GVariantBuilder <span class="hl opt">*</span>builder<span class="hl opt">;</span>
  GVariantBuilder <span class="hl opt">*</span>invalidated_builder<span class="hl opt">;</span>
  GError <span class="hl opt">*</span>error<span class="hl opt">;</span>

  swap_a_and_b <span class="hl opt">= !</span>swap_a_and_b<span class="hl opt">;</span>

  error <span class="hl opt">=</span> NULL<span class="hl opt">;</span>
  builder <span class="hl opt">=</span> <span class="hl kwd">g_variant_builder_new</span> <span class="hl opt">(</span>G_VARIANT_TYPE_ARRAY<span class="hl opt">);</span>
  invalidated_builder <span class="hl opt">=</span> <span class="hl kwd">g_variant_builder_new</span> <span class="hl opt">(</span><span class="hl kwd">G_VARIANT_TYPE</span> <span class="hl opt">(</span><span class="hl str">&quot;as&quot;</span><span class="hl opt">));</span>
  <span class="hl kwd">g_variant_builder_add</span> <span class="hl opt">(</span>builder<span class="hl opt">,</span>
                         <span class="hl str">&quot;{sv}&quot;</span><span class="hl opt">,</span>
                         <span class="hl str">&quot;Foo&quot;</span><span class="hl opt">,</span>
                         <span class="hl kwd">g_variant_new_string</span> <span class="hl opt">(</span>swap_a_and_b ? <span class="hl str">&quot;Tock&quot;</span> <span class="hl opt">:</span> <span class="hl str">&quot;Tick&quot;</span><span class="hl opt">));</span>
  <span class="hl kwd">g_variant_builder_add</span> <span class="hl opt">(</span>builder<span class="hl opt">,</span>
                         <span class="hl str">&quot;{sv}&quot;</span><span class="hl opt">,</span>
                         <span class="hl str">&quot;Bar&quot;</span><span class="hl opt">,</span>
                         <span class="hl kwd">g_variant_new_string</span> <span class="hl opt">(</span>swap_a_and_b ? <span class="hl str">&quot;Tick&quot;</span> <span class="hl opt">:</span> <span class="hl str">&quot;Tock&quot;</span><span class="hl opt">));</span>
  <span class="hl kwd">g_dbus_connection_emit_signal</span> <span class="hl opt">(</span>connection<span class="hl opt">,</span>
                                 NULL<span class="hl opt">,</span>
                                 <span class="hl str">&quot;/org/gtk/GDBus/TestObject&quot;</span><span class="hl opt">,</span>
                                 <span class="hl str">&quot;org.freedesktop.DBus.Properties&quot;</span><span class="hl opt">,</span>
                                 <span class="hl str">&quot;PropertiesChanged&quot;</span><span class="hl opt">,</span>
                                 <span class="hl kwd">g_variant_new</span> <span class="hl opt">(</span><span class="hl str">&quot;(sa{sv}as)&quot;</span><span class="hl opt">,</span>
                                                <span class="hl str">&quot;org.gtk.GDBus.TestInterface&quot;</span><span class="hl opt">,</span>
                                                builder<span class="hl opt">,</span>
                                                invalidated_builder<span class="hl opt">),</span>
                                 <span class="hl opt">&amp;</span>error<span class="hl opt">);</span>
  <span class="hl kwd">g_assert_no_error</span> <span class="hl opt">(</span>error<span class="hl opt">);</span>


  <span class="hl kwa">return</span> TRUE<span class="hl opt">;</span>
<span class="hl opt">}</span>

<span class="hl com">/* ---------------------------------------------------------------------------------------------------- */</span>

<span class="hl kwb">static void</span>
<span class="hl kwd">on_bus_acquired</span> <span class="hl opt">(</span>GDBusConnection <span class="hl opt">*</span>connection<span class="hl opt">,</span>
                 <span class="hl kwb">const</span> gchar     <span class="hl opt">*</span>name<span class="hl opt">,</span>
                 gpointer         user_data<span class="hl opt">)</span>
<span class="hl opt">{</span>
  guint registration_id<span class="hl opt">;</span>

  registration_id <span class="hl opt">=</span> <span class="hl kwd">g_dbus_connection_register_object</span> <span class="hl opt">(</span>connection<span class="hl opt">,</span>
                                                       <span class="hl str">&quot;/org/gtk/GDBus/TestObject&quot;</span><span class="hl opt">,</span>
                                                       introspection_data<span class="hl opt">-&gt;</span>interfaces<span class="hl opt">[</span><span class="hl num">0</span><span class="hl opt">],</span>
                                                       <span class="hl opt">&amp;</span>interface_vtable<span class="hl opt">,</span>
                                                       NULL<span class="hl opt">,</span>  <span class="hl com">/* user_data */</span>
                                                       NULL<span class="hl opt">,</span>  <span class="hl com">/* user_data_free_func */</span>
                                                       NULL<span class="hl opt">);</span> <span class="hl com">/* GError** */</span>
  <span class="hl kwd">g_assert</span> <span class="hl opt">(</span>registration_id <span class="hl opt">&gt;</span> <span class="hl num">0</span><span class="hl opt">);</span>

  <span class="hl com">/* swap value of properties Foo and Bar every two seconds */</span>
  <span class="hl kwd">g_timeout_add_seconds</span> <span class="hl opt">(</span><span class="hl num">2</span><span class="hl opt">,</span>
                         on_timeout_cb<span class="hl opt">,</span>
                         connection<span class="hl opt">);</span>
<span class="hl opt">}</span>

<span class="hl kwb">static void</span>
<span class="hl kwd">on_name_acquired</span> <span class="hl opt">(</span>GDBusConnection <span class="hl opt">*</span>connection<span class="hl opt">,</span>
                  <span class="hl kwb">const</span> gchar     <span class="hl opt">*</span>name<span class="hl opt">,</span>
                  gpointer         user_data<span class="hl opt">)</span>
<span class="hl opt">{</span>
<span class="hl opt">}</span>

<span class="hl kwb">static void</span>
<span class="hl kwd">on_name_lost</span> <span class="hl opt">(</span>GDBusConnection <span class="hl opt">*</span>connection<span class="hl opt">,</span>
              <span class="hl kwb">const</span> gchar     <span class="hl opt">*</span>name<span class="hl opt">,</span>
              gpointer         user_data<span class="hl opt">)</span>
<span class="hl opt">{</span>
  <span class="hl kwd">exit</span> <span class="hl opt">(</span><span class="hl num">1</span><span class="hl opt">);</span>
<span class="hl opt">}</span>

<span class="hl kwb">int</span>
<span class="hl kwd">main</span> <span class="hl opt">(</span><span class="hl kwb">int</span> argc<span class="hl opt">,</span> <span class="hl kwb">char</span> <span class="hl opt">*</span>argv<span class="hl opt">[])</span>
<span class="hl opt">{</span>
  guint owner_id<span class="hl opt">;</span>
  GMainLoop <span class="hl opt">*</span>loop<span class="hl opt">;</span>

  <span class="hl com">/* We are lazy here - we don't want to manually provide</span>
<span class="hl com">   * the introspection data structures - so we just build</span>
<span class="hl com">   * them from XML.</span>
<span class="hl com">   */</span>
  introspection_data <span class="hl opt">=</span> <span class="hl kwd">g_dbus_node_info_new_for_xml</span> <span class="hl opt">(</span>introspection_xml<span class="hl opt">,</span> NULL<span class="hl opt">);</span>
  <span class="hl kwd">g_assert</span> <span class="hl opt">(</span>introspection_data <span class="hl opt">!=</span> NULL<span class="hl opt">);</span>

  owner_id <span class="hl opt">=</span> <span class="hl kwd">g_bus_own_name</span> <span class="hl opt">(</span>G_BUS_TYPE_SESSION<span class="hl opt">,</span>
                             <span class="hl str">&quot;org.gtk.GDBus.TestServer&quot;</span><span class="hl opt">,</span>
                             G_BUS_NAME_OWNER_FLAGS_NONE<span class="hl opt">,</span>
                             on_bus_acquired<span class="hl opt">,</span>
                             on_name_acquired<span class="hl opt">,</span>
                             on_name_lost<span class="hl opt">,</span>
                             NULL<span class="hl opt">,</span>
                             NULL<span class="hl opt">);</span>

  loop <span class="hl opt">=</span> <span class="hl kwd">g_main_loop_new</span> <span class="hl opt">(</span>NULL<span class="hl opt">,</span> FALSE<span class="hl opt">);</span>
  <span class="hl kwd">g_main_loop_run</span> <span class="hl opt">(</span>loop<span class="hl opt">);</span>

  <span class="hl kwd">g_bus_unown_name</span> <span class="hl opt">(</span>owner_id<span class="hl opt">);</span>

  <span class="hl kwd">g_dbus_node_info_unref</span> <span class="hl opt">(</span>introspection_data<span class="hl opt">);</span>

  <span class="hl kwa">return</span> <span class="hl num">0</span><span class="hl opt">;</span>
<span class="hl opt">}</span>
</code></pre></td></tr></table>
</div> <!-- class=content -->
</div>
  <div id="footer_community"></div>

  <div id="footer_grass"></div>

  <div id="footer">
    <div class="container_13" id="container_12">
      <div class="links grid_9">
        <div class="menu-footer-container">
          <ul id="menu-footer" class="menu">
            <li id="menu-item-1048" class=
            "menu-item menu-item-type-custom menu-item-object-custom current-menu-item current_page_item menu-item-1048">
            <a href="/">The GNOME Project</a>

              <ul class="sub-menu">
                <li id="menu-item-1049" class=
                "menu-item menu-item-type-post_type menu-item-object-page menu-item-1049">
                <a href="https://www.gnome.org/about/">About Us</a></li>

                <li id="menu-item-1050" class=
                "menu-item menu-item-type-post_type menu-item-object-page menu-item-1050">
                <a href="https://www.gnome.org/get-involved/">Get Involved</a></li>

                <li id="menu-item-1051" class=
                "menu-item menu-item-type-post_type menu-item-object-page menu-item-1051">
                <a href="https://www.gnome.org/teams/">Teams</a></li>

                <li id="menu-item-1053" class=
                "menu-item menu-item-type-post_type menu-item-object-page menu-item-1053">
                <a href="https://www.gnome.org/support-gnome/">Support GNOME</a></li>

                <li id="menu-item-1054" class=
                "menu-item menu-item-type-post_type menu-item-object-page menu-item-1054">
                <a href="https://www.gnome.org/contact/">Contact Us</a></li>

                <li id="menu-item-2246" class=
                "menu-item menu-item-type-post_type menu-item-object-page menu-item-2246">
                <a href="https://www.gnome.org/foundation/">The GNOME Foundation</a></li>
              </ul>
            </li>

            <li id="menu-item-1047" class=
            "menu-item menu-item-type-custom menu-item-object-custom menu-item-1047">
              <a href="#">Resources</a>

              <ul class="sub-menu">
                <li id="menu-item-1055" class=
                "menu-item menu-item-type-custom menu-item-object-custom menu-item-1055">
                <a href="https://developer.gnome.org">Developer Center</a></li>

                <li id="menu-item-1056" class=
                "menu-item menu-item-type-custom menu-item-object-custom menu-item-1056">
                <a href="https://help.gnome.org">Documentation</a></li>

                <li id="menu-item-1057" class=
                "menu-item menu-item-type-custom menu-item-object-custom menu-item-1057">
                <a href="https://wiki.gnome.org">Wiki</a></li>

                <li id="menu-item-1058" class=
                "menu-item menu-item-type-custom menu-item-object-custom menu-item-1058">
                <a href="https://mail.gnome.org/mailman/listinfo">Mailing Lists</a></li>

                <li id="menu-item-1059" class=
                "menu-item menu-item-type-custom menu-item-object-custom menu-item-1059">
                <a href="https://wiki.gnome.org/GnomeIrcChannels">IRC Channels</a></li>

                <li id="menu-item-1060" class=
                "menu-item menu-item-type-custom menu-item-object-custom menu-item-1060">
                <a href="https://bugzilla.gnome.org/">Bug Tracker</a></li>

                <li id="menu-item-1061" class=
                "menu-item menu-item-type-custom menu-item-object-custom menu-item-1061">
                <a href="https://git.gnome.org/browse/">Development Code</a></li>

                <li id="menu-item-1062" class=
                "menu-item menu-item-type-custom menu-item-object-custom menu-item-1062">
                <a href="https://wiki.gnome.org/Jhbuild">Build Tool</a></li>
              </ul>
            </li>

            <li id="menu-item-1046" class=
            "menu-item menu-item-type-custom menu-item-object-custom menu-item-1046">
              <a href="/news">News</a>

              <ul class="sub-menu">
                <li id="menu-item-1063" class=
                "menu-item menu-item-type-post_type menu-item-object-page menu-item-1063">
                <a href="https://www.gnome.org/press/">Press Releases</a></li>

                <li id="menu-item-1064" class=
                "menu-item menu-item-type-custom menu-item-object-custom menu-item-1064">
                <a href="https://www.gnome.org/start/stable">Latest Release</a></li>

                <li id="menu-item-1065" class=
                "menu-item menu-item-type-custom menu-item-object-custom menu-item-1065">
                <a href="https://planet.gnome.org">Planet GNOME</a></li>

                <li id="menu-item-1067" class=
                "menu-item menu-item-type-custom menu-item-object-custom menu-item-1067">
                <a href="https://news.gnome.org">Development News</a></li>

                <li id="menu-item-1068" class=
                "menu-item menu-item-type-custom menu-item-object-custom menu-item-1068">
                <a href="https://identi.ca/gnome">Identi.ca</a></li>

                <li id="menu-item-1069" class=
                "menu-item menu-item-type-custom menu-item-object-custom menu-item-1069">
                <a href="https://twitter.com/gnome">Twitter</a></li>
              </ul>
            </li>
          </ul>
        </div>
      </div>

      <div id="footnotes" class="grid_9">
<p>Copyright &copy; 2004&ndash;2015, <a href="https://www.gnome.org/">The GNOME Project</a>.</p>
<br />
  <small><p>Hosted by <a href="http://www.redhat.com/">Red Hat</a>. 
   Powered by <a href="http://hjemli.net/git/cgit/">cgit</a>.</p>
  <p>To follow the commits, subscribe to <a href="http://mail.gnome.org/mailman/listinfo/commits-list">commits-list</a>. (can be limited to specific modules)</p></small>
</div>
    </div>
  </div>
</div> <!-- id=cgit -->
</body>
</html>
