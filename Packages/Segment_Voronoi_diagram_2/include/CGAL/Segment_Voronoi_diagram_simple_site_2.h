// Copyright (c) 2003,2004  INRIA Sophia-Antipolis (France) and
// Notre Dame University (U.S.A.).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source$
// $Revision$ $Date$
// $Name$
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>



#ifndef SEGMENT_VORONOI_DIAGRAM_SIMPLE_SITE_H
#define SEGMENT_VORONOI_DIAGRAM_SIMPLE_SITE_H

#include <iostream>
#include <CGAL/assertions.h>

#include <CGAL/Segment_Voronoi_diagram_short_names_2.h>

#include <CGAL/Segment_Voronoi_diagram_constructions_C2.h>

CGAL_BEGIN_NAMESPACE

  /** A Site is either a point or a segment or a point defined as the
      intersection of two non-parallel segments (if defined)
   */

template <class R_>
class Segment_Voronoi_diagram_simple_site_2 
{
public:
  typedef R_ R;
  typedef R  Rep;
  typedef typename R::Point_2   Point_2;
  typedef typename R::Segment_2 Segment_2;

protected:
  typedef typename R::FT        FT;
  typedef typename R::RT        RT;
  typedef Segment_Voronoi_diagram_simple_site_2<Rep>  Self;

  //  friend class Construct_svd_site_2<Self,Tag_false>;

  //  friend std::ostream& operator<<(std::ostream&, const Self&);
  //  friend std::istream& operator>>(std::istream&, Self&);

public:
  static Self construct_site_2(const Point_2& p) {
    Self t;
    t.initialize_site(p);
    return t;
    //    return Self(p);
  }

  static Self construct_site_2(const Point_2& p0, const Point_2& p1) {
    Self t;
    t.initialize_site(p0, p1);
    return t;
    //    return Self(p0, p1);
  }

 private:
  static bool no_warning(bool b) {
    CGAL_assertion( b );
    return b;
  }

  static void no_constructor_support() {
    bool THIS_CLASS_DOES_NOT_SUPPORT_THIS_CONSTRUCTOR = false;
    no_warning( THIS_CLASS_DOES_NOT_SUPPORT_THIS_CONSTRUCTOR );
  }

 public:
  // these "constructors" are defined in order to conform with the
  // specs; they will produce a run-time error if used
  static Self construct_site_2(const Point_2& p1, const Point_2& p2,
			       const Point_2& q1, const Point_2& q2) {
    no_constructor_support();
    return Self();
  }

  static Self construct_site_2(const Point_2& p1, const Point_2& p2,
			       const Point_2& q1, const Point_2& q2,
			       bool b) {
    no_constructor_support();
    return Self();
  }

  static Self construct_site_2(const Point_2& p1, const Point_2& p2,
			       const Point_2& q1, const Point_2& q2,
			       const Point_2& r1, const Point_2& r2) {
    no_constructor_support();
    return Self();
  }

public:
  Segment_Voronoi_diagram_simple_site_2() : type_(0) {}

public:
  bool is_defined() const { return type_; }
  bool is_point() const { return type_ == 1; }
  bool is_segment() const { return type_ == 2; }
  bool is_input() const { return true; }
  bool is_input(unsigned int i) const { return true; }

  const Point_2& point() const { 
    CGAL_precondition ( is_point() );
    return p_[0];
  }

  const Point_2& source_of_supporting_site() const {
    CGAL_precondition( is_segment() );
    return p_[0];
  }

  const Point_2& target_of_supporting_site() const {
    CGAL_precondition( is_segment() );
    return p_[1];
  }

  // the following four methods do not really make any sense but have
  // been added in order for this class to be a model of the
  // SegmentVoronoiDiagramSite_2 concept.
  const Point_2& source_of_supporting_site(unsigned int i) const {
    CGAL_precondition( is_point() && !is_input() );
    return p_[0];
  }

  const Point_2& target_of_supporting_site(unsigned int i) const {
    CGAL_precondition( is_point() && !is_input() );
    return p_[0];
  }

  const Point_2& source_of_crossing_site(unsigned int i) const {
    CGAL_precondition( is_segment() && !is_input(i) );
    return p_[0];
  }

  const Point_2& target_of_crossing_site(unsigned int i) const {
    CGAL_precondition( is_segment() && !is_input(i) );
    return p_[0];
  }


  Segment_2 segment() const {
    CGAL_precondition ( is_segment() ); 
    return Segment_2( p_[0], p_[1] );
  }

  const Point_2& source() const {
    CGAL_precondition ( is_segment() ); 
    return p_[0];
  }

  const Point_2& target() const {
    CGAL_precondition ( is_segment() ); 
    return p_[1];
  }

  Self source_site() const {
    CGAL_precondition( is_segment() );
    return Self::construct_site_2(p_[0]);
  }

  Self target_site() const {
    CGAL_precondition( is_segment() );
    return Self::construct_site_2(p_[1]);
  }

  const Self& supporting_site() const {
    CGAL_precondition( is_segment() );
    return *this;
  }

  // the following two methods make no sense, but have been added in
  // order for this class to be a model of the
  // SegmentVoronoiDiagramSite_2 concept.
  Self supporting_site(unsigned int i) const {
    CGAL_precondition( is_point() && i < 2 );
    CGAL_precondition( !is_input() );
    return Self::construct_site_2(p_[0], p_[0]);
  }

  Self crossing_site(unsigned int i) const {
    CGAL_precondition( is_segment() && i < 2 );
    CGAL_precondition( !is_input(i) );
    return *this;
  }

protected:
  void initialize_site(const Point_2& p)
  {
    type_ = 1;
    p_[0] = p;
  }

  void initialize_site(const Point_2& p1, const Point_2& p2)
  {
    type_ = 2;
    p_[0] = p1;
    p_[1] = p2;
  }

protected:
  Point_2 p_[2];
  char type_;
};

//-------------------------------------------------------------------------

template <class R>
std::ostream&
operator<<(std::ostream& os, 
	   const Segment_Voronoi_diagram_simple_site_2<R>& s)
{
  if (!s.is_defined())
    return os << "u";
  if (s.is_point())
    return os << "p " << s.point ();
  return os << "s " << s.segment ();
}

template <class R>
std::istream &
operator>>(std::istream &is,
	   Segment_Voronoi_diagram_simple_site_2<R>& t)
{
  typedef Segment_Voronoi_diagram_simple_site_2<R>   Site_2;
  typedef typename Site_2::Point_2                   Point_2;

  char type;
  if (is >> type) {
    if (type == 'p') {
      Point_2 p;
      is >> p;
      t = Site_2::construct_site_2(p);
    } else if (type == 's') {
      Point_2 p1, p2;
      is >> p1 >> p2;
      t = Site_2::construct_site_2(p1, p2);
    }
  }
  return is;
}

template < class R, class Stream >
Stream&
operator<<(Stream& str, Segment_Voronoi_diagram_simple_site_2<R>& t)
{
  if ( t.is_defined() ) {
    if ( t.is_point() ) {
      str << "p " << t.point();
    } else {
      str << "s " << t.segment().source() << "  "
	  << t.segment().target();
    }
  }

  return str;
}


CGAL_END_NAMESPACE

#endif // SEGMENT_VORONOI_DIAGRAM_SIMPLE_SITE_H
