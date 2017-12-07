


 float energy=0, contrast=0, homogenity=0, dissimilarity=0, correlation=0, clustershade=0, IDM=0,entropy=0,mean1=0;













////////////////////////////////////////////////
dissimilarity += ( gl.at<float>(i,j) * abs(i-j));

correlation += (i*j) * ( gl.at<float>(i,j) - (mean0[0]*mean0[0]));

if(gl.at<float>(i,j)!=0)
	entropy=entropy-gl.at<float>(i,j)*log10(gl.at<float>(i,j));

mean1=mean1+0.5*(i*gl.at<float>(i,j)+j*gl.at<float>(i,j));

clustershade += pow((float)((i - mean0[0]) + (j - mean0[0])),3) * gl.at<float>(i,j);

if(i!=j)
	IDM=IDM+gl.at<float>(i,j)/((i-j)*(i-j));
	

	
cout<<"\n\n";
cout<<"moyenne=\t\t"<<mean0(0)<<endl;
cout<<"standard deviation=\t"<<stdv(0)<<endl;
cout<<"energy=\t\t\t"<<energy<<endl;
cout<<"contrast=\t\t"<<contrast<<endl;
cout<<"homogenity=\t\t"<<homogenity<<endl;
cout<<"dissimilarity=\t\t"<<dissimilarity<<endl;
cout<<"correlation=\t\t"<<correlation<<endl;
cout<<"entropy=\t\t"<<entropy<<endl;

cout<<"clustershade=\t\t"<<clustershade<<endl;
cout<<"mean1=\t\t\t"<<mean1<<endl;

cout<<"IDM=\t\t\t"<<IDM<<endl;


cout<<"\n\n";