//expanded_utils_test.cpp william k. johnson 2015


#include <cci_numeric_utils.h>
#include <cci_complexity.h>
#include <cci_concurrent_utils.h>

using namespace cci_expansion;

struct func
{
    int& i;
    func( int& i_ ) : i{ i_ } {}

    void operator() ()
    {
        for( unsigned j = 0; j < 1000; ++j )
        {
            ++i;
            std::cout << i;
        }
        std::cout << "\n";
    }
};

int main( int argc , char* argv[] )
{

    std::vector<int> v_dw { 1, 2 , 3 , 4 , 5 }    ;
    std::default_random_engine dre( 7 );
    std::uniform_int_distribution<int> di( 10 , 20 );

    //shuffle - unseeded
    /*std::vector<int> v_dw_shuffled { shuffle_t( v_dw , dre ) };
    for( auto elem : v_dw_shuffled ) { std::cout << elem << " "; }
    std::cout << "\n";
    v_dw_shuffled = shuffle_t( v_dw , dre );
    for( auto elem : v_dw_shuffled ) { std::cout << elem << " "; }
    std::cout << "\n";


    //generate random - closed range with ints , half open with floats
    //unseeded
    gen_random_init_t( v_dw_shuffled , di , dre );
    for( auto elem : v_dw_shuffled ) { std::cout << elem << " "; }
    std::cout << "\n";*/

    //std::unique_ptr<random_default_manip> manip( new random_default_manip( v_dw , di , dre ) );
    /*ceu_random_manip_t<std::vector<int> ,
                       std::uniform_int_distribution<int>  ,
                       std::default_random_engine> manip( v_dw , di , dre ) ;
    */
    //manip->shuffle_t();
    //
    int dw { 100 };
    func the_function( dw );
    std::thread thr( the_function );
    thread_raii<std::thread> g( thr ,
                                dtor_action::join );
    std::thread thr_2( the_function );
    scoped_thread<std::thread> st( thr_2 );

    std::string str( "abcdefghiabcdx" );
    baby_bits bb;
    char_count cc;

    ascii_bits ab  = bb.chars_in_str( str , &cc );
    std::cout << "char\t\t\tchar occurrence\n\n";
    std::for_each( cc.begin() ,
                   cc.end() ,
                   [] ( std::pair<const char,unsigned long>& elem )
                   {
                        std::cout << elem.first
                                  << "\t\t\t"
                                  << elem.second
                                  << "\n";
                   }
                 );
    std::cout << "chars not in string: ";
    for( int i = 0; i < ab.size(); i++ )
    {
        if( ab.test( i ) == false && isalpha( i ) ) { std::cout << (char) i; }
    }
    std::cout << "\n";

    /*for( auto elem : *manip.collection() ) { std::cout << elem << " "; }
    std::cout << "\n";
    manip.shuffle_t();
    for( auto elem : *manip.collection() ) { std::cout << elem << " "; }
    std::cout << "\n";*/





    return ( 0 );
}


/*{
    edge g = std::make_tuple( "foo" , "jim" );
    edge r = std::make_tuple( "jim" , "bar" );
    //
    vertex m( "foo" );
    vertex s( "bar" );
    vertex k( "jim" );
    //graph g;
    std::vector<edge> x;
    x.push_back( g );
    x.push_back( r );
    std::vector<vertex> v;
    v.push_back( m );
    v.push_back( s );
    v.push_back( k );
    cc_graph ccg( &v , &x);
    std::pair<bool,edge> pr = ccg.retr_edge( k , s );
    std::cout << pr.second << "\n";
    vertices vs = ccg.enum_vertices();
    std::vector<edge> se;
    se = ccg.enum_edges();*/

