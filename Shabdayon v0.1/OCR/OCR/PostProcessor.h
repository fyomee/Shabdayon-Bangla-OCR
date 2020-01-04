

#pragma once

ref class PostProcessor
{
private: System::String^ processStr;
private: bool IsDependentVowel(wchar_t Vowel)
		 {
			 const wchar_t aakar = 2494;
			 const wchar_t rossoikar = 2495;
			 const wchar_t dirgikar = 2496;
			 const wchar_t rossoUkar = 2497;
			 const wchar_t dirgUkar = 2498;
			 const wchar_t rrikar = 2499;
			 const wchar_t ekar = 2503;
			 const wchar_t oikar = 2504;
			 const wchar_t o_kar = 2507;
			 const wchar_t ou_kar = 2508;

			 switch(Vowel)
			 {
			 case aakar:
			 case rossoikar:
			 case dirgikar:
			 case rossoUkar:
			 case dirgUkar:
			 case rrikar:
			 case ekar:
			 case oikar:
			 case o_kar:
			 case ou_kar:
				 return true;
				 break;
			 };

			 return false;
		 }

public:
	PostProcessor(System::String^ textStr)
	{
		this->processStr = textStr;
	}

	~PostProcessor(){
		processStr = "";
	}

public: System::String^ TextPostProcessor2()
		{
			int i;
			bool b;
			wchar_t chr2Set1;
			wchar_t chr2Set2;

			this->processStr = this->processStr->Trim();
			cli::array<wchar_t,1>^ ch = this->processStr->ToCharArray();
			int len = this->processStr->Length;

			System::Collections::ArrayList^ charU = gcnew System::Collections::ArrayList(len);

			// copy characters into list
			for(i=0;i<len;i++){
				charU->Add(ch[i]);
			}

			const wchar_t space = 32;
			const wchar_t ex_sign = 33;
			const wchar_t dot = 46;
			const wchar_t comma = 44;
			const wchar_t dash = 45;

			const wchar_t chandrabindu = 2433;
			const wchar_t a = 2437;
			const wchar_t Aa = 2438;
			const wchar_t aakar = 2494;
			const wchar_t dirgikar = 2496;
			const wchar_t ekar = 2503;
			const wchar_t oikar = 2504;
			const wchar_t o_kar = 2507;
			const wchar_t ou_kar = 2508;
			const wchar_t hasanta = 2509;
			const wchar_t dari = 2404;
			const wchar_t rossoUkar = 2497;
			const wchar_t dirgUkar = 2498;
			const wchar_t rrikar = 2499;
			const wchar_t za = 2479;
			const wchar_t onisar = 2434;

			wchar_t presChar;

			for( i = 0; i < charU->Count; i++ )
			{
				presChar = (wchar_t) charU[i];

				if(presChar == dari){
					presChar = presChar;
				}
				/* Rule - 1
				* If there is any 2 Consecutive char is vowel 
				and they are same then delete any one */
				if ((i + 1 < charU->Count) && this->IsDependentVowel(presChar) && this->IsDependentVowel((wchar_t)charU[i + 1])){
						if (presChar == charU[i + 1]) {
							charU->RemoveAt(i);
						}
				}

				/* Rule - 2
				* Few character/modifier/symbol cannot appear at the beginning of a word
				* Example: onisar, aa-kar, daari, exclamatory sign, comma, dot, hasant 
				* if any of such comes at the beganing of a word then remove it */
				if ((i==0 && (i + 1 < charU->Count)) && ((presChar==onisar) || (presChar==aakar) || (presChar==dari) || (presChar==ex_sign) || (presChar==comma) || (presChar==dot) || (presChar==hasanta)))
				{
					if (((i - 1 < 0) || ((wchar_t)charU[i - 1] == space)) && ((wchar_t)charU[i + 1] != space)) {
						charU->RemoveAt(i);
						i--;

						// special condition for the hashant as the next character is za (hashant+za = za-fola)
						if((i >= 0) && presChar==hasanta){
							charU->RemoveAt(i);
							i--;
						}
					}
				} else if ((presChar == chandrabindu) && (i + 1 < charU->Count)) {
					// changing position of chandrabindu with dependant vowel
					// rule is : consonant + dependant vowel + chandrabindu
					if ((wchar_t)charU[i+1] == aakar) {
						wchar_t tmp = (wchar_t) charU[i+1];// copy aakar
						charU->RemoveAt(i+1);
						charU->Insert(i+1, presChar);
						charU->RemoveAt(i);
						charU->Insert(i, tmp);
					}
				} else if (presChar == hasanta)//2509
				{
					// solving the problem of zofala
					// zofala always sits befor dependent vowel
					// here we r moving zofala before dependent vowel
					if ((i + 1 < charU->Count) && ((wchar_t)charU[i+1] == za)) {
						if ((i - 1 > 0) && this->IsDependentVowel((wchar_t)charU[i-1])) {
							wchar_t tmp = (wchar_t) charU[i-1];// copy dependent vowel
							chr2Set1 = (wchar_t)charU[i+1];
							
							charU->RemoveAt(i-1);
							charU->Insert(i-1, presChar);
							charU->RemoveAt(i);
							charU->Insert(i, chr2Set1);
							charU->RemoveAt(i+1);
							charU->Insert(i+1, tmp);
						}
					}// end zofala

				}//end of hasanta				 

				//////////////////////////////////////////////////////////////////////////
				switch (presChar) {
				case a:
					// If there is a aakar/daari/ex_sign/za-fola after an a(Sori_O), then we are replace this both 
					/// as Aa(Sori_Aa)
					if (i+1 < charU->Count){
						// for aakar/daari/ex_sign
						wchar_t nextChar = (wchar_t) charU[i+1];

						if (nextChar == aakar || nextChar == dari || nextChar == ex_sign) {
							charU->RemoveAt(i);
							charU->RemoveAt(i);
							charU->Insert(i, Aa);
						}
					}
					else if ((i+2 < charU->Count) && ((wchar_t)charU[i+1]==hasanta) && ((wchar_t)charU[i+2]==za)) {
						// for za-fola
						charU->RemoveAt(i);
						charU->RemoveAt(i);
						charU->RemoveAt(i);
						charU->Insert(i, Aa);
					}

					break;

				case aakar:
					///Here we r converting the aakar to dari. if an aakar have space of its
					///before and after, then we r replace the aakar as dari
					if (i > 0 && ((wchar_t)charU[i-1] == space))
					{
						//charU.set(i,dari);
						charU->RemoveAt(i);
						charU->Insert(i, dari);
					}
					// If any aakar is followed by any aakar/o_kar/ou_kar then replace it with dari
					else if ((i-1 > 0) && (((wchar_t)charU[i-1] == aakar)  || ((wchar_t)charU[i-1] == o_kar) || ((wchar_t)charU[i-1] == ou_kar)))
					{
						charU->RemoveAt(i);
						charU->Insert(i, space);
						charU->Insert(i,dari);
					}

					break;

				case rossoUkar:
					// pass control to next
				case dirgUkar:
					// pass control to next

				case rrikar:
					b = presChar == rossoUkar || presChar == dirgUkar || presChar == rrikar;//

					// If any lower modifier (rossu-kar, dirghu-kar and re-kar) is followed by aa-kar then just remove it
					// This condition will be false if the previous character is zo-fala. So, we need to check the existance of zo-fola first

					if((i-2 > 0) && ((wchar_t)charU[i-1]==za) && ((wchar_t)charU[i-2]==hasanta)){
						// za-fola exists. so make status of b as false
						b = false;
					}

					// apply rules of lower modifiers followed by aakar
					if (b && (i + 1 < charU->Count) && ((wchar_t)charU[i+1]==aakar)) {
						charU->RemoveAt(i);
					}
					else if (b && (i + 2 < charU->Count ) && ((wchar_t)charU[i+1]==dari)){// || charU[i+1))==ex_sign)) {
						// sometime dari and ex_sign takes place of aa-kar. So, need to handle this
						charU->RemoveAt(i);
						charU->RemoveAt(i);
						charU->Insert(i, aakar);
					}
					else if (b && i-1>0 && ((wchar_t)charU[i-1]==ekar)) {
						charU->RemoveAt(i);
					}

					break;
				case ekar:
					// pass control to next
				case oikar:

					b = presChar == ekar || presChar == oikar;//

					if (b && i + 1 < charU->Count) {
						int k = i + 1;//next char

						// swapping 
						wchar_t tmp = presChar;// ekar or oikar  this char
						chr2Set1 = (wchar_t)charU[k];

						charU->RemoveAt(i);
						charU->Insert(i, chr2Set1);
						charU->RemoveAt(k);
						charU->Insert(k, tmp);

						k = k + 1;
						// for compound char 
						while ((k + 1 < charU->Count - 1) && ((wchar_t)charU[k] == hasanta)) {
							chr2Set1 = (wchar_t)charU[k];
							chr2Set2 = (wchar_t)charU[k+1];

							//charU.set(k-1, charU[k]);
							charU->RemoveAt(k-1);
							charU->Insert(k-1, chr2Set1);

							//charU.set(k, charU[k+1]);
							charU->RemoveAt(k);
							charU->Insert(k, chr2Set2);

							//charU.set(k+1, tmp);
							charU->RemoveAt(k+1);
							charU->Insert(k+1, tmp);

							k += 2;
						}
							i = k - 1;
					}// end ekar or oikar prob

					// solving ekar + aakar = o_kar
					if ((i + 1 < charU->Count) && (presChar == ekar) && ((wchar_t)charU[i+1] == aakar)) {
							charU->RemoveAt(i);
							charU->Insert(i, o_kar);
							charU->RemoveAt(i + 1);
							i--;
					} // solving ekar + dirgikar = ou_kar
					else if ((i + 1 < charU->Count) && (presChar == ekar) && ((wchar_t)charU[i+1] == dirgikar)) {
							charU->RemoveAt(i);
							charU->Insert(i, ou_kar);
							charU->RemoveAt(i + 1);
							i--;
					}
					// end case 
					break;

				case dari:
					if (i > 0 && ((wchar_t)charU[i-1] != space) && ((wchar_t)charU[i-1] != aakar) && ((wchar_t)charU[i-1] != o_kar) && ((wchar_t)charU[i-1] != ou_kar)){
						//charU.set(i,aakar);
						charU->RemoveAt(i);
						charU->Insert(i, aakar);
					}
					break;

				case ex_sign:
					if ((i+1 < charU->Count) && ((wchar_t)charU[i+1] == space)){
						break;
					}

					if ((i > 0 && i != charU->Count-1) && ((wchar_t)charU[i-1] != space)){
						//charU.set(i,aakar);
						charU->RemoveAt(i);
						charU->Insert(i, aakar);
					}
					break;

				case dot:
					int endIndex = charU->Count-1;
					if (i < endIndex){
						charU->RemoveAt(i);
					}
					else{
						charU->RemoveAt(i);
						charU->Insert(i, comma);
					}
					break;
				}


			}// end for

			len = charU->Count;
			wchar_t *ch1 = new wchar_t[len+1];

			for (int m = 0; m < len; m++)
				ch1[m] = (wchar_t)charU[m];

			ch1[len] = '\0';
			System::String^ s = gcnew System::String(ch1);
			delete[] ch1;
			return s;
		}/// end
};
