<storytool created-with="512" file="1">
	<project main-graph="" name="Untitled Project">
		<characters>
			<character name="Player">
				<color>255</color>
				<description>The playable character.</description>
			</character>
		</characters>
		<storyline template="C-I">
			<storylines>
				<line id="Player-0">Hallo Welt.</line>
				<line id="End">End of the Story :(</line>
				<line id="Player-1">Ich bin ein Test!</line>
				<line id="CP">Checkpoint reached</line>
			</storylines>
		</storyline>
		<globals>
			<global id="g">10,000000</global>
			<global id="h">5,000000</global>
			<global id="i">-3,000000</global>
			<global id="j">2,940000</global>
		</globals>
		<nodes>
			<node character="Player" id="Action">
				<nodestyle position="2f(426,000000|1292,371704)">
					<text>
						Action
						<size>30</size>
						<color>7929855</color>
					</text>
					<color>2564618495</color>
				</nodestyle>
				<storylines></storylines>
				<is_activated></is_activated>
				<after_execute></after_execute>
			</node>
			<node character="Player" id="Checkpoint">
				<nodestyle position="2f(400,000092|1443,106201)">
					<text>
						Checkpoint
						<size>30</size>
						<color>4060020991</color>
					</text>
					<color>4456447</color>
				</nodestyle>
				<storylines></storylines>
				<is_activated></is_activated>
				<after_execute></after_execute>
			</node>
			<node character="Player" id="Negative Action">
				<nodestyle position="2f(701,759644|1573,709717)">
					<text>
						Negative Action
						<size>30</size>
						<color>255</color>
					</text>
					<color>2717975039</color>
				</nodestyle>
				<storylines></storylines>
				<is_activated></is_activated>
				<after_execute></after_execute>
			</node>
			<node character="Player" id="Positive Action">
				<nodestyle position="2f(703,299866|1774,154297)">
					<text>
						Positive Action
						<size>30</size>
						<color>255</color>
					</text>
					<color>347144447</color>
				</nodestyle>
				<storylines></storylines>
				<is_activated></is_activated>
				<after_execute></after_execute>
			</node>
		</nodes>
		<graphs>
			<graph id="main">
				<text>
					<size>30</size>
					<color>4294967295</color>
				</text>
				<description>The main Graph in the project.</description>
				<nodes>
					<node character="Player" id="9">
						<nodestyle position="2f(426,000000|1292,371704)">
							<text>
								Action
								<size>30</size>
								<color>7929855</color>
							</text>
							<color>2564618495</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="1">
						<nodestyle position="2f(284,000122|416,884949)">
							<text>
								Negative Action
								<size>30</size>
								<color>255</color>
							</text>
							<color>2717975039</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="2">
						<nodestyle position="2f(391,000122|128,035400)">
							<text>
								Action
								<size>30</size>
								<color>7929855</color>
							</text>
							<color>2564618495</color>
						</nodestyle>
						<storylines>
							<storyline>Player-0</storyline>
							<storyline>Player-1</storyline>
						</storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="3">
						<nodestyle position="2f(520,000000|554,938049)">
							<text>
								Positive Action
								<size>30</size>
								<color>255</color>
							</text>
							<color>347144447</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="4">
						<nodestyle position="2f(175,000061|543,256592)">
							<text>
								Negative Action
								<size>30</size>
								<color>255</color>
							</text>
							<color>2717975039</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="5">
						<nodestyle position="2f(613,000061|697,238953)">
							<text>
								Checkpoint
								<size>30</size>
								<color>4060020991</color>
							</text>
							<color>4456447</color>
						</nodestyle>
						<storylines>
							<storyline>CP</storyline>
						</storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="6">
						<nodestyle position="2f(377,000092|827,858459)">
							<text>
								Positive Action
								<size>30</size>
								<color>255</color>
							</text>
							<color>347144447</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="7">
						<nodestyle position="2f(374,000000|986,530945)">
							<text>
								Negative Action
								<size>30</size>
								<color>255</color>
							</text>
							<color>2717975039</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="8">
						<nodestyle position="2f(378,999969|1166,000000)">
							<text>
								Negative Action
								<size>30</size>
								<color>255</color>
							</text>
							<color>2717975039</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="10">
						<nodestyle position="2f(333,538055|1869,728394)">
							<text>
								Checkpoint
								<size>30</size>
								<color>4060020991</color>
							</text>
							<color>4456447</color>
						</nodestyle>
						<storylines>
							<storyline>End</storyline>
						</storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="11">
						<nodestyle position="2f(400,000092|1443,106201)">
							<text>
								Checkpoint
								<size>30</size>
								<color>4060020991</color>
							</text>
							<color>4456447</color>
						</nodestyle>
						<storylines>
							<storyline>CP</storyline>
						</storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="12">
						<nodestyle position="2f(88,289673|1573,709717)">
							<text>
								Negative Action
								<size>30</size>
								<color>255</color>
							</text>
							<color>2717975039</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="13">
						<nodestyle position="2f(383,909607|1549,274170)">
							<text>
								Negative Action
								<size>30</size>
								<color>255</color>
							</text>
							<color>2717975039</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="14">
						<nodestyle position="2f(703,059692|1601,320313)">
							<text>
								Negative Action
								<size>30</size>
								<color>255</color>
							</text>
							<color>2717975039</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="15">
						<nodestyle position="2f(-88,400085|1771,393188)">
							<text>
								Positive Action
								<size>30</size>
								<color>255</color>
							</text>
							<color>347144447</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="16">
						<nodestyle position="2f(180,699890|1775,534790)">
							<text>
								Positive Action
								<size>30</size>
								<color>255</color>
							</text>
							<color>347144447</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="17">
						<nodestyle position="2f(443,299957|1779,676392)">
							<text>
								Positive Action
								<size>30</size>
								<color>255</color>
							</text>
							<color>347144447</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
					<node character="Player" id="18">
						<nodestyle position="2f(703,299866|1774,154297)">
							<text>
								Positive Action
								<size>30</size>
								<color>255</color>
							</text>
							<color>347144447</color>
						</nodestyle>
						<storylines></storylines>
						<is_activated></is_activated>
						<after_execute></after_execute>
					</node>
				</nodes>
				<connections>
					<connection end="1" start="2"></connection>
					<connection end="3" start="1"></connection>
					<connection end="4" start="1"></connection>
					<connection end="5" start="3"></connection>
					<connection end="6" start="5"></connection>
					<connection end="6" start="4"></connection>
					<connection end="7" start="6"></connection>
					<connection end="8" start="7"></connection>
					<connection end="9" start="8"></connection>
					<connection end="11" start="9"></connection>
					<connection end="12" start="11"></connection>
					<connection end="13" start="11"></connection>
					<connection end="14" start="11"></connection>
					<connection end="15" start="12"></connection>
					<connection end="16" start="12"></connection>
					<connection end="17" start="14"></connection>
					<connection end="14" start="14"></connection>
					<connection end="18" start="14"></connection>
					<connection end="10" start="13"></connection>
				</connections>
				<subgraphs>
					<subgraph id="Test">2f(100,000000|100,000000)</subgraph>
				</subgraphs>
			</graph>
			<graph id="Test">
				<text>
					Test Graph
					<size>30</size>
					<color>4294967295</color>
				</text>
				<description></description>
				<nodes></nodes>
				<connections></connections>
				<subgraphs></subgraphs>
			</graph>
		</graphs>
	</project>
</storytool>
