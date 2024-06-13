PGDMP  9                    |            InLink    16.2    16.2 -    �           0    0    ENCODING    ENCODING        SET client_encoding = 'UTF8';
                      false            �           0    0 
   STDSTRINGS 
   STDSTRINGS     (   SET standard_conforming_strings = 'on';
                      false            �           0    0 
   SEARCHPATH 
   SEARCHPATH     8   SELECT pg_catalog.set_config('search_path', '', false);
                      false            �           1262    16417    InLink    DATABASE     �   CREATE DATABASE "InLink" WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE_PROVIDER = libc LOCALE = 'English_United States.1252';
    DROP DATABASE "InLink";
                postgres    false            �            1259    16425 	   abilities    TABLE     T   CREATE TABLE public.abilities (
    id integer NOT NULL,
    skill text NOT NULL
);
    DROP TABLE public.abilities;
       public         heap    postgres    false            �            1259    16424    abilities_id_seq    SEQUENCE     �   CREATE SEQUENCE public.abilities_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 '   DROP SEQUENCE public.abilities_id_seq;
       public          postgres    false    216            �           0    0    abilities_id_seq    SEQUENCE OWNED BY     E   ALTER SEQUENCE public.abilities_id_seq OWNED BY public.abilities.id;
          public          postgres    false    215            �            1259    16525    accounts    TABLE     �   CREATE TABLE public.accounts (
    account_id integer NOT NULL,
    user_id integer,
    last_view timestamp without time zone DEFAULT CURRENT_TIMESTAMP
);
    DROP TABLE public.accounts;
       public         heap    postgres    false            �            1259    16524    accounts_account_id_seq    SEQUENCE     �   CREATE SEQUENCE public.accounts_account_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 .   DROP SEQUENCE public.accounts_account_id_seq;
       public          postgres    false    228            �           0    0    accounts_account_id_seq    SEQUENCE OWNED BY     S   ALTER SEQUENCE public.accounts_account_id_seq OWNED BY public.accounts.account_id;
          public          postgres    false    227            �            1259    16442    cities    TABLE     O   CREATE TABLE public.cities (
    country_id integer,
    city text NOT NULL
);
    DROP TABLE public.cities;
       public         heap    postgres    false            �            1259    16452 	   companies    TABLE     U   CREATE TABLE public.companies (
    country_id integer,
    company text NOT NULL
);
    DROP TABLE public.companies;
       public         heap    postgres    false            �            1259    16434 	   countries    TABLE     S   CREATE TABLE public.countries (
    id integer NOT NULL,
    name text NOT NULL
);
    DROP TABLE public.countries;
       public         heap    postgres    false            �            1259    16433    countries_id_seq    SEQUENCE     �   CREATE SEQUENCE public.countries_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 '   DROP SEQUENCE public.countries_id_seq;
       public          postgres    false    218            �           0    0    countries_id_seq    SEQUENCE OWNED BY     E   ALTER SEQUENCE public.countries_id_seq OWNED BY public.countries.id;
          public          postgres    false    217            �            1259    16478 
   job_groups    TABLE     [   CREATE TABLE public.job_groups (
    group_id integer NOT NULL,
    title text NOT NULL
);
    DROP TABLE public.job_groups;
       public         heap    postgres    false            �            1259    16477    job_groups_group_id_seq    SEQUENCE     �   CREATE SEQUENCE public.job_groups_group_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 .   DROP SEQUENCE public.job_groups_group_id_seq;
       public          postgres    false    223            �           0    0    job_groups_group_id_seq    SEQUENCE OWNED BY     S   ALTER SEQUENCE public.job_groups_group_id_seq OWNED BY public.job_groups.group_id;
          public          postgres    false    222            �            1259    16491    jobs    TABLE     S   CREATE TABLE public.jobs (
    job_group_id integer,
    job_name text NOT NULL
);
    DROP TABLE public.jobs;
       public         heap    postgres    false            �            1259    16467    universities    TABLE     [   CREATE TABLE public.universities (
    country_id integer,
    university text NOT NULL
);
     DROP TABLE public.universities;
       public         heap    postgres    false            <           2604    16428    abilities id    DEFAULT     l   ALTER TABLE ONLY public.abilities ALTER COLUMN id SET DEFAULT nextval('public.abilities_id_seq'::regclass);
 ;   ALTER TABLE public.abilities ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    215    216    216            ?           2604    16528    accounts account_id    DEFAULT     z   ALTER TABLE ONLY public.accounts ALTER COLUMN account_id SET DEFAULT nextval('public.accounts_account_id_seq'::regclass);
 B   ALTER TABLE public.accounts ALTER COLUMN account_id DROP DEFAULT;
       public          postgres    false    227    228    228            =           2604    16437    countries id    DEFAULT     l   ALTER TABLE ONLY public.countries ALTER COLUMN id SET DEFAULT nextval('public.countries_id_seq'::regclass);
 ;   ALTER TABLE public.countries ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    218    217    218            >           2604    16481    job_groups group_id    DEFAULT     z   ALTER TABLE ONLY public.job_groups ALTER COLUMN group_id SET DEFAULT nextval('public.job_groups_group_id_seq'::regclass);
 B   ALTER TABLE public.job_groups ALTER COLUMN group_id DROP DEFAULT;
       public          postgres    false    222    223    223            �          0    16425 	   abilities 
   TABLE DATA                 public          postgres    false    216   �-       �          0    16525    accounts 
   TABLE DATA                 public          postgres    false    228   �/       �          0    16442    cities 
   TABLE DATA                 public          postgres    false    219   �/       �          0    16452 	   companies 
   TABLE DATA                 public          postgres    false    220   �1       �          0    16434 	   countries 
   TABLE DATA                 public          postgres    false    218   26       �          0    16478 
   job_groups 
   TABLE DATA                 public          postgres    false    223   �6       �          0    16491    jobs 
   TABLE DATA                 public          postgres    false    224   �7       �          0    16467    universities 
   TABLE DATA                 public          postgres    false    221   L:       �           0    0    abilities_id_seq    SEQUENCE SET     ?   SELECT pg_catalog.setval('public.abilities_id_seq', 30, true);
          public          postgres    false    215            �           0    0    accounts_account_id_seq    SEQUENCE SET     F   SELECT pg_catalog.setval('public.accounts_account_id_seq', 1, false);
          public          postgres    false    227            �           0    0    countries_id_seq    SEQUENCE SET     ?   SELECT pg_catalog.setval('public.countries_id_seq', 1, false);
          public          postgres    false    217            �           0    0    job_groups_group_id_seq    SEQUENCE SET     F   SELECT pg_catalog.setval('public.job_groups_group_id_seq', 1, false);
          public          postgres    false    222            B           2606    16432    abilities abilities_pkey 
   CONSTRAINT     V   ALTER TABLE ONLY public.abilities
    ADD CONSTRAINT abilities_pkey PRIMARY KEY (id);
 B   ALTER TABLE ONLY public.abilities DROP CONSTRAINT abilities_pkey;
       public            postgres    false    216            H           2606    16531    accounts accounts_pkey 
   CONSTRAINT     \   ALTER TABLE ONLY public.accounts
    ADD CONSTRAINT accounts_pkey PRIMARY KEY (account_id);
 @   ALTER TABLE ONLY public.accounts DROP CONSTRAINT accounts_pkey;
       public            postgres    false    228            D           2606    16441    countries countries_pkey 
   CONSTRAINT     V   ALTER TABLE ONLY public.countries
    ADD CONSTRAINT countries_pkey PRIMARY KEY (id);
 B   ALTER TABLE ONLY public.countries DROP CONSTRAINT countries_pkey;
       public            postgres    false    218            F           2606    16485    job_groups job_groups_pkey 
   CONSTRAINT     ^   ALTER TABLE ONLY public.job_groups
    ADD CONSTRAINT job_groups_pkey PRIMARY KEY (group_id);
 D   ALTER TABLE ONLY public.job_groups DROP CONSTRAINT job_groups_pkey;
       public            postgres    false    223            M           2606    16532    accounts accounts_user_id_fkey    FK CONSTRAINT     }   ALTER TABLE ONLY public.accounts
    ADD CONSTRAINT accounts_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id);
 H   ALTER TABLE ONLY public.accounts DROP CONSTRAINT accounts_user_id_fkey;
       public          postgres    false    228            I           2606    16447    cities cities_country_id_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.cities
    ADD CONSTRAINT cities_country_id_fkey FOREIGN KEY (country_id) REFERENCES public.countries(id);
 G   ALTER TABLE ONLY public.cities DROP CONSTRAINT cities_country_id_fkey;
       public          postgres    false    4676    219    218            J           2606    16457 #   companies companies_country_id_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.companies
    ADD CONSTRAINT companies_country_id_fkey FOREIGN KEY (country_id) REFERENCES public.countries(id);
 M   ALTER TABLE ONLY public.companies DROP CONSTRAINT companies_country_id_fkey;
       public          postgres    false    220    218    4676            L           2606    16496    jobs jobs_job_group_id_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.jobs
    ADD CONSTRAINT jobs_job_group_id_fkey FOREIGN KEY (job_group_id) REFERENCES public.job_groups(group_id);
 E   ALTER TABLE ONLY public.jobs DROP CONSTRAINT jobs_job_group_id_fkey;
       public          postgres    false    223    224    4678            K           2606    16472 )   universities universities_country_id_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.universities
    ADD CONSTRAINT universities_country_id_fkey FOREIGN KEY (country_id) REFERENCES public.countries(id);
 S   ALTER TABLE ONLY public.universities DROP CONSTRAINT universities_country_id_fkey;
       public          postgres    false    218    221    4676            �   �  x���[o�@��ɯط�Ԣ��Ҋ��M R�Qmx�lg�^��q��zf�����x�3{fη�*��]#VeS�C�Ѩ^�j$� ��ן�����R\�An���C�ŋKVsV����T��
FZقKIx��'�6�Up���a�Z��^�>���������Ix|���k���Z�ힽ�tM�x(:+ȉ-�D��+�J�?e��gSVoAa`����9L+�RU�\��F�V����������0f=)���֣�b�r����`�1K쾁��qO�[B��.�-���ۑ������za\xE�ZcV��!���vO�!"���$hQ=��,���f �7������w�O�yֳ�x�O�����4!��e>K ����#ݥ�8<�<b����GJy���yf��9 ��p�VZ�,�x�~�]'?�^�ƨn���uAhn�}4����>��m�p�JH������/In5�      �   
   x���          �   �  x���Mo�0��˯�-+P[��a��M���ހ�X�X+b!Ym�_?)u ��C:�)�/E�y���X�W{����-���3�~/�ɻ�/ٴ�B��^\�:5;1(j8]A�1�k0B@�>90�V41X��2�A.t�Q4�G�M/X����o�4��M��Z����$���+W&#�����إ�
nz���ޣj�[J0-���3�ODc��}���=��X��pF��T�%7&��R +��?u��FW�z��/����^��­z���6�[�����>��$�����Ǣ��f@�ÍYZG�l�����@��ƞ��/�6`�8R��X��/Pu��J�@J��А�r�$�"�Ѥ��������ɤ�7\�HΝe���w$;�! oY��X��]���y��&�O�t}�����l��E���K�fL���1uY� Ȼ��(�@�%�n������/2U)�      �   �  x��VYo�8~��
>5��M�E�d'>_����H[�iR!��ί�!�C�c��/��7��7��n6g��|²<<n�j���h�S0|�/����5���J�`MZ�l��x����z�rJ���D��p�"а��U��i�g��q~z�X�)Z���<v!�$7V�g5����:*�P�<�r�F(�VG`KL-�a�+So��ZA��\./��d�:�qw8���턍'��`��q1���|)8�,��6����J۴��/>`�!m2�t/���� z�u��g�,h멟���=��8F\Vo�}��)�������ݜ���MO!��\Ri���S�9e�d������x��Lą?�=S��6�1�zJQU��v���H(��	���5�����G��U�J`�����kkn�IY�F�7��cUE�
�����[K��g\�9�V���L��vd�@깸U��5�+�,�
����b����R��A?�VF-,����b8��c���v��Q��6�I�F��5Vp�Ri�d���_I5)�t#%��訒�Ƙ�T~��[Gt{�=��|9��y��I�
Nr�.5Y{�\��ET��bn�[�G[�]ޕ��עfЌ�^�펜��e�e0��3y��yl�b�mlȩ�0)<���˘�ס�~o�)�8�J�e�Z�lh���I�F+�z�y�n��X ��A�:v��Y7��}ðwh�Y�Ǯ��Fm��UI�qg���Gz��|��r�N����E���f�q���7��!MN�5FjMG��>��%w�g&������w�' ��V�:�rF�3��Ծ���׵5$h�OUy�k�`����nMB��_����;�p;ٙ�|s3]��X~�T
���`������t�������o�B�eL9�����g�i�Atu���`TE�n����L.�uY�Oˎ��u��o�9��x������=����*��_��pX���TJ��w���>�߆���(�ۙ� ��u1��h����>����cy�����.F�Q��Q�t�0�͒���&����c��ui�H?c�=ʻݡ�J&G�yV�YX��L簤������?ɘC���-�<ˈ~���ԯ����-w���16U����D^��ṙٹ�����      �   �   x�5���0@ѵ���!	1�q��X%mb���$6���������d(�Ee�C��J���Wk���a�ł�� <j��� 5qz;�QIa��|\X`��(�%rg�W�Ϋ�����F�m�XU�i�餪�����<�fz>pg��F��Gʒ-!�Y�2�      �   �   x�m̽� ��Y��۪Ic������TH��jZJ���r�~ѱ��sr/iQ㕀.6����7|�z���-�d�H!�����
@�6N�`�Nf)���m��u�zU�Y;#k;�5:�J�o�����]����ik$n1���	~�YV�Q Յ�����C<      �   �  x��UMs�0=�_�[ڙL?�������N��"�D�<���������$G�v���]Gq2�OY�sV����^Z�{8}�$�w�?_��D���1nQ��Ň�=6,��ֵ���а�љ�<�^:�w`VU�ʄ��3�V,RkmrpB+���an�d�7_�8���g�f�7T�M�*��}z�Ko�"S��\���,��*��p�p6��h�L�Q��s�ӻ(��1��G�[�{��Ҡ�#rwF���G::���eP�7��襐�E��7)�
$Ya�c�3�ȁY�n��S˰shX�E]��ġy"NZ��&u��{�m��������k�kz��c��P��>�����=��F	2I���u"���	%�x���e�ۛ-��{�y�z�l�!�P�dNˠ�t\�_m�k/�*��ɤ�D�ѫ@�;�k'���]U���8�q:��e4�p"�U-�Q5ȵ�9�*�N�;�Rʮ�������$AMuyh-�7�rޣ�,e��M�v��zΐW�hylD	ýp}P%	߀��-��U���~�a�9�]�Yk�Vw�-��3�m(L�ՠt��Igdg5�F�l�d��K����L®�>r�=�QF�S��O4������_�"$�x�+`s�}QQ����E�q�g�О�G����Ë�� �VW      �   �  x��W�o�8��~�R�B�w��w��$-�BD�V��`���v�K��;@�XtR�������|�0Jn)	�tN�r�s:,�Δ�3M���mr����k�)å���
A�<'�� vd�������l1�>�+%k�L.A��Hb;׀�c���,�Z[:xڸ��$fFI��-���X��(K�H$�a�I��t���,8�E��IGQ���a�x!3��ܙ�P�iDH瀷 VE�ȵ3#�����2��>�<"�<M� %7s��I����o
?WYy����v��bőT&�����ZA֎�?n"��K��ݗjŵ�-ئ��X"1�e��bܰ��͸@���@:�Է9�����l� 7�9^h��.��2���c����Ǥ�i���^��4;$�zi�'����WX����C&[n����V>�3�Ж>��%b]��u�B�:#ޖa�1�)v.����00����V�pذx�%I�0���៖CQ�ۓ+WN��w)�Tn����`Ɍ��X�Mήj��S%�\,
��v%Q�G@�Rʗ�α)�V�
}�^t�#0`�u w2Z
rI���x&��N�4CD �1@�ټ�~�.��N��p��"�o�=A�q�ҊΰiuK�Ϟ�߰CRM�+��YM��ka�dD���6�{8HA��q�#S��Lp��;��C�Ź�KX¾=�mG����*�_\����ؗ=Ĥ�7Ƒ1̈́��Z"�k25�a2.����f�rX@8@���b��O\;ǜ���F��s}z�Ψ�ں��NA�7Lܪ=�UC�G�R;d�ʭ-��nn��p!F{�fx���6���6���K���a�ڌ\I�~��x��n�T��V���d�kQh�$8_��L�����W�b��w~ґx�%��=b1�Hp���%�;������ �xd��I�l_R�|�
ÂR0�|�}s5��zw<�U�T�Î5�9`5��U�X|��?1⅒}��fv���\� 2�^���g�u�R��x?��8�xh��y��M_Vd;]�7��9���qLC�{b�@��`o��Òi;�R��; u�w��{F3��%`����m9��@�E�G��Ǘ��<��X�r'��F�~�,"�8cNjf��r��$NFwd�3H���r�e�F���5�H�����]�mm�=��Z�m�N����j8s��&�nύ�"s��~�}
�fv���w�Ö�R7V�	�����4[�_�2$     